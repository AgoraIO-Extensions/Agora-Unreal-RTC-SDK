import {
  CXXTYPE,
  ConstructorInitializer,
  MemberFunction,
  MemberVariable,
  SimpleType,
} from '@agoraio-extensions/cxx-parser/src/cxx_terra_node';

import { get } from 'lodash';

import * as Logger from '../logger';

import * as Tools from '../tools';

import * as BPHelper from './bp_helper';

import * as BPNameHelper from './bpname_helper';

import {
  ConversionWayType,
  CppBPConversionData,
  DeclTypeSPRule,
  UEBPTypeConvData,
  map_bptype_conv_data,
  map_cppreg_2_bptype_conv_data,
  map_one_category_basicconv_bpfromcpp,
  map_one_category_basicconv_cppfrombp,
  map_struct_member_variable_default_value,
} from './bptype_data_conv';
import {
  ClazzAddtionalContext_,
  map_class_initialization,
} from './bptype_data_makeup';
import { AGORA_MUSTACHE_DATA } from './bptype_mustache_data';

export function getBPTypeConvData(
  typeSource: string
): UEBPTypeConvData | undefined {
  const data_bptype_conv = map_bptype_conv_data[typeSource];
  if (!data_bptype_conv) {
    for (const [
      regex,
      regex_bptype_convdata,
    ] of map_cppreg_2_bptype_conv_data.entries()) {
      // TBD(WinterPu):
      // what if one pattern meets multiple regex

      // reset regex lastIndex:
      // so it would not be affected by previous test
      regex.lastIndex = 0;
      if (regex.test(typeSource)) {
        return regex_bptype_convdata;
      }
    }
    Logger.PrintWarn('' + typeSource + ' not found in map_bptype_conv_data');
  }
  return data_bptype_conv;
}

export class UEBPType {
  cppTypeName: string;
  cppDeclType: string;
  cppTypeSource: string;

  // Direct Convert
  // BP
  // Ex. cpp type source: const char **
  // [bpTypeName]: type name of blueprint: Ex. FString: used in the case: call class static method: FString::FromCStr()
  //  or used in template type UABT::SetBPArrayData<FString, TArray<FString>(BPVar, CppArrayVar, CppArraySize);
  name: string;
  // [bpDeclType]: type name with some properties: Ex. TArray<FString>: used in the variable declaration: TArray<FString> MyArray; (usually in the function implementation)
  declType: string;
  // [bpTypeSource]: type with full qualifier: Ex. const TArray<FString> &: used in the function parameter: void MyFunc(const TArray<FString> &MyArray);
  source: string;

  // Extra:
  // [bpDelegateType] used in bp multicast-delegate: Ex. const TArray<FString> & (because delegates don't support non-const reference)
  delegateType: string;

  isTArray: boolean;
  isPointer: boolean;

  // bp = FuncFrom(cpp);
  bpConv_BPFromCpp: CppBPConversionData;
  // bpNeedConvFunc_BPFromCpp: boolean;
  // bpConvWayType_BPFromCpp: ConvWayType_BPFromCpp;
  // bpNameConvFunc_BPFromCpp: string;

  // cpp = FuncTo(bp);
  bpConv_CppFromBP: CppBPConversionData;
  // bpNeedConvFunc_CppFromBP: boolean;
  // bpConvWayType_CppFromBP: ConvWayType_CppFromBP;
  // bpNameConvFunc_CppFromBP: string;
  // // Example:
  // // bpNameConvFunc_CppFromBP [NewRawData]
  // // bpNameConvFuncAdditional_CppFromBP: [FreeRawData]
  // bpNameConvFuncAdditional_CppFromBP: string;

  // Convert In Impl:
  bpConvDeclTypeSPRule: DeclTypeSPRule;

  constructor() {
    this.cppTypeName = '';
    this.cppDeclType = '';
    this.cppTypeSource = '';

    this.name = '';
    this.source = '';
    this.declType = '';
    this.delegateType = '';

    this.isTArray = false;
    this.isPointer = false;

    this.bpConv_BPFromCpp = {
      convFuncType: ConversionWayType.NoNeedConversion,
      convFunc: '',
      convFuncAdditional01: '',
    } as CppBPConversionData;

    this.bpConv_CppFromBP = {
      convFuncType: ConversionWayType.NoNeedConversion,
      convFunc: '',
      convFuncAdditional01: '',
    } as CppBPConversionData;

    this.bpConvDeclTypeSPRule = DeclTypeSPRule.DefaultNoSP;
  }

  toString(): string {
    return `UEBPType {
        // C++ Type Info:
        cppTypeName: "${this.cppTypeName}"
        cppTypeDeclType: "${this.cppDeclType}"
        cppTypeSource: "${this.cppTypeSource}"

        // Blueprint Type Info:
        name: "${this.name}"  // Blueprint type name
        source: "${this.source}"  // Blueprint type with qualifiers
        declType: "${this.declType}"  // Blueprint type name with properties
        delegateType: "${
          this.delegateType
        }"  // Blueprint type name for delegate

        isTArray: ${this.isTArray}
        isPointer: ${this.isPointer}

        // Conversion from C++ to BP:
        bpConv_BPFromCpp: "${this.bpConv_BPFromCpp.toString()}"

        // Conversion from BP to C++:
        bpConv_CppFromBP: "${this.bpConv_CppFromBP.toString()}"

        // Decl Type:
        bpConvDeclTypeSPRule: "${this.bpConvDeclTypeSPRule}"
    }`;
  }
}

function genBPConvertFromRawType(
  type: SimpleType,
  isTArray: boolean
): CppBPConversionData {
  // bp = Func(cpp);
  let conversion: CppBPConversionData = {
    convFuncType: ConversionWayType.NoNeedConversion,
    convFunc: '',
    convFuncAdditional01: '',
  };

  const [typeCategory, bpTypeNameTmp] = BPHelper.getBPName(type);

  // Enum
  if (typeCategory == CXXTYPE.Enumz) {
    conversion = map_one_category_basicconv_bpfromcpp.get('Enum')!;
  }

  if (isTArray) {
    //TBD(WinterPu)
    // need to distinguish:
    // for: raw type
    // USTRUCT
    // UCLASS
    let key_label = 'TArray';
    if (typeCategory === CXXTYPE.Clazz) {
      // for UCLASS
      key_label = 'TArray_UCLASS';
    } else if (typeCategory === CXXTYPE.Struct) {
      // for USTRUCT
      key_label = 'TArray_USTRUCT';
    } else {
      // for other types including raw type
      key_label = 'TArray';
    }

    conversion = map_one_category_basicconv_bpfromcpp.get(key_label)!;
  }

  const type_conv_data = getBPTypeConvData(type.source);
  if (type_conv_data) {
    conversion = type_conv_data.convFromCpp;
  }

  return conversion;
}

function genBPConvertToRawType(
  type: SimpleType,
  isTArray: boolean
): CppBPConversionData {
  // cpp = Func(bp);
  let conversion: CppBPConversionData = {
    convFuncType: ConversionWayType.NoNeedConversion,
    convFunc: '',
    convFuncAdditional01: '',
  };

  const [typeCategory, bpTypeNameTmp] = BPHelper.getBPName(type);
  // UEnum
  if (typeCategory == CXXTYPE.Enumz) {
    conversion = map_one_category_basicconv_cppfrombp.get('Enum')!;
  }

  if (typeCategory === CXXTYPE.Clazz || typeCategory === CXXTYPE.Struct) {
    if (BPNameHelper.isCustomDefinedBPType_Optional(type)) {
      conversion = map_one_category_basicconv_cppfrombp.get('Optional')!;
    } else {
      conversion = map_one_category_basicconv_cppfrombp.get('UCLASS_USTRUCT')!;
    }
  }

  if (isTArray) {
    let key_label = 'TArray';
    if (typeCategory === CXXTYPE.Clazz) {
      // for UCLASS
      key_label = 'TArray_UCLASS';
    } else if (typeCategory === CXXTYPE.Struct) {
      // for USTRUCT
      key_label = 'TArray_USTRUCT';
    } else {
      // for other types including raw type
      key_label = 'TArray';
    }

    conversion = map_one_category_basicconv_cppfrombp.get(key_label)!;
  }

  const type_conv_data = getBPTypeConvData(type.source);
  if (type_conv_data) {
    conversion = type_conv_data.convToCpp;
  }

  return conversion;
}

export function parsePointerType(
  type: SimpleType,
  refBPTypeName: string = 'only_check_if_it_is_an_array'
): [boolean, string] {
  // keep the pointer type, not as array type
  // Ex. agora::rtc::IScreenCaptureSourceList* => UAgoraBPuScreenCaptureSourceList *
  const type_source = type.source ?? '';
  const data_type_conv = getBPTypeConvData(type_source);
  const need_keep = data_type_conv?.parsePointerForceEnable ?? false;
  if (need_keep) {
    return [true, refBPTypeName + ' *'];
  }
  return [false, type.source];
}

// TBD(WinterPu) - TArray<char>
// 函数：检查字符串是否为数组类型，并返回类型名或原始类型
//// we use: regex + blacklist + whitelist

// TBD(WinterPu)
// to fix: virtual int getCaches(MusicCacheInfo *cacheInfo, int32_t* cacheInfoSize) = 0;
//  int32_t* cacheInfoSize would be TArray<int>
export function parseArrayType(
  typeSource: string,
  refBPTypeName: string = 'only_check_if_it_is_an_array',
  isReturnType?: boolean,
  options?: AnalysisOptions
): [boolean, string] {
  // // Regex to check
  // // 匹配格式为 typeName[n] 或 typeName[] 的字符串
  // const regex = /^(.*?)(\[\d+\]|\[\])$/;
  // const match = regex.exec(typeSource);

  let basicMatch = analyzeBasicArrayType(typeSource, isReturnType, options);

  const data_bptype_conv = getBPTypeConvData(typeSource);

  // Black List
  if (data_bptype_conv && data_bptype_conv.parseArrayIsInBlackList) {
    return [false, typeSource];
  }
  // White List
  // TBD(WinterPu):
  // It would have (const int* list, int listNum)
  // Should combine them together
  if (data_bptype_conv && data_bptype_conv.parseArrayDesignedType) {
    return [false, data_bptype_conv.parseArrayDesignedType];
  }

  // TBD(WinterPu):
  // you may defined in [map_parse_array_whitelist] and it doesn't match [refBPTypeName]
  // 如果匹配成功，返回 true 和类型名
  if (basicMatch.isArray || basicMatch.isPointer) {
    // Here, if it is a array, you should use [refBPTypeName]

    if (refBPTypeName.includes(AGORA_MUSTACHE_DATA.UEBP_PREFIX_CLASS)) {
      // TArray UCLASS should be pointer
      refBPTypeName = refBPTypeName + ' *';
    }
    let matched_array_type = 'TArray<' + refBPTypeName + '>';
    return [true, matched_array_type]; // match[1] 是去掉数组标记后的类型名
  }

  // 如果不匹配，返回 false 和原始类型
  return [false, typeSource];
}

export function analyzeBasicArrayType(
  typeSource: string,
  isReturnType?: boolean,
  options?: AnalysisOptions
): {
  isArray: boolean;
  isPointer: boolean;
  baseType: string;
  size?: number;
  isNamespaced: boolean;
  isSpecialExempt?: boolean;
} {
  const data_bptype_conv = getBPTypeConvData(typeSource);

  // 去掉const关键字和规范化空格
  let normalizedType = typeSource.replace(/\bconst\b/g, '').trim();
  normalizedType = normalizedType.replace(/\s+/g, ' ');

  let result = {
    isArray: false,
    isPointer: false,
    baseType: typeSource,
    size: undefined as number | undefined,
    isNamespaced: normalizedType.includes('::'),
    isSpecialExempt: false,
  };

  // [Exclude] Void
  if (typeSource.toLowerCase().includes('void')) {
    result.isSpecialExempt = true;
    return result;
  }

  // TBD(WinterPu)
  // cause Circular Reference
  //[Exclude] 检查是否是豁免的特殊类型（包含Observer或EventHandler的类型）
  const map_clazz = BPHelper.getMapCpp2BPClass();
  if (map_clazz.has(typeSource) && Tools.isMatch(typeSource, 'isCallback')) {
    result.isSpecialExempt = true;
    return result;
  }

  // [Exclude]
  if (options?.isAgoraType && isReturnType) {
    result.isSpecialExempt = true;
    return result;
  }

  // // [Exclude]
  // if (isReturnType) {
  //   if (not_parse_array_type_for_return_type.includes(typeSource)) {
  //     result.isSpecialExempt = true;
  //     return result;
  //   }
  // }

  // 检查是否是数组类型，例如 T[N]
  const arrayRegex = /^(.+?)\s*\[(\d+)\]$/;
  const arrayMatch = normalizedType.match(arrayRegex);

  if (arrayMatch) {
    result.isArray = true;
    result.baseType = arrayMatch[1].trim();
    result.size = parseInt(arrayMatch[2], 10);
    return result;
  }

  // 检查是否是指针类型，例如 T*
  const pointerRegex = /^(.+?)\s*\*$/;
  const pointerMatch = normalizedType.match(pointerRegex);

  if (pointerMatch) {
    result.isPointer = true;
    result.baseType = pointerMatch[1].trim();
    return result;
  }

  return result;
}

// 辅助函数：检查是否是特定类型的指针
export function isPointerToType(
  typeSource: string,
  targetType: string
): boolean {
  const analysis = analyzeBasicArrayType(typeSource);
  // 创建一个不区分大小写、忽略空格的比较
  const normalizedBaseType = analysis.baseType
    .replace(/\s+/g, '')
    .toLowerCase();
  const normalizedTarget = targetType.replace(/\s+/g, '').toLowerCase();

  return analysis.isPointer && normalizedBaseType.includes(normalizedTarget);
}

// 检查是否是字符数组
export function isCharArrayType(typeSource: string): {
  isArray: boolean;
  size?: number;
} {
  const analysis = analyzeBasicArrayType(typeSource);

  // 是否是固定大小的字符数组
  if (
    analysis.isArray &&
    (analysis.baseType === 'char' || analysis.baseType === 'const char')
  ) {
    return { isArray: true, size: analysis.size };
  }

  // 是否是字符指针
  if (
    analysis.isPointer &&
    (analysis.baseType === 'char' || analysis.baseType === 'const char')
  ) {
    return { isArray: false };
  }

  return { isArray: false };
}

// 定义一个接口
export interface AnalysisOptions {
  methodName?: string;
  variableName?: string;
  isAgoraType?: boolean;
}
/* 
            "type": {
                "__TYPE": "SimpleType",
                "is_builtin_type": true,
                "is_const": true,
                "kind": 101,
                "name": "char",
                "source": "char const*",
                "template_arguments": []
            }


            "return_type": {
              "__TYPE": "SimpleType",
              "is_builtin_type": false,
              "is_const": false,
              "kind": 102,
              "name": "CopyableAutoPtr<T>",
              "source": "CopyableAutoPtr<T>&",
              "template_arguments": []
            },
            "signature": "(const CopyableAutoPtr<T>&)",
            "source": ""


            "type": {
                "__TYPE": "SimpleType",
                "is_builtin_type": false,
                "is_const": true,
                "kind": 102,
                "name": "agora::rtc::RtcConnection",
                "source": "agora::rtc::RtcConnection const&",
                "template_arguments": []
            }

            "type": {
              "__TYPE": "SimpleType",
              "is_builtin_type": false,
              "is_const": false,
              "kind": 104,
              "name": "Optional",
              "source": "Optional<bool>",
              "template_arguments": ["bool"]
            }
*/
export function convertToBPType(
  type: SimpleType,
  isOutput?: boolean,
  isReturnType?: boolean,
  options?: AnalysisOptions
): UEBPType {
  let result = new UEBPType();
  result.cppTypeName = type.name;
  result.cppTypeSource = type.source;
  Logger.Print(`convertToBPType: ${type.source}`);
  // **** First Step: Directly Searching in the map ****
  // Try to get [bpTypeName]

  // use [source type] to get a full type
  // builtin type: usually directly set value.
  // Mapping multiple times
  // Try to get the type name of Blueprint
  // [ nameType / SourceType ] => [ bpTypeName ]

  // Here, almost you got the built-in unreal blueprint type
  const data_bptype_conv = getBPTypeConvData(type.source);
  const tmpTypeName_DirectMappingResult = data_bptype_conv?.bpTypeName ?? '';

  if (!Tools.isNullOrEmpty(tmpTypeName_DirectMappingResult)) {
    result.name = tmpTypeName_DirectMappingResult;
  } else {
    // Not Founded

    // use [type name] to get a bp type name
    let bFounded = false;
    const data_bptype_conv_typename = getBPTypeConvData(type.name);
    if (data_bptype_conv_typename) {
      result.name = data_bptype_conv_typename.bpTypeName;
      bFounded = true;
    }

    if (!bFounded) {
      // **** Second Step: If failed, analyze the type ****
      // Try to get [bpTypeName]

      // Enum / Class / Struct's name is without namespace
      // type.name has namespace
      // TBD(WinterPu):
      // 1. is it possible to have namespace in the middle[ex. Optional<agora::rtc::RtcConnection>]
      let [typeCategory, bpTypeNameTmp] = BPHelper.getBPName(type);

      if (typeCategory != CXXTYPE.Unknown) {
        result.name = bpTypeNameTmp;
      } else {
        Logger.PrintError(
          `convertToBPType: No Conversion Mapping ${type.source}`
        );
        result.name = type.name;
      }
    }
  }

  // **** Third Step: Get [bpTypeSource] from [bpTypeName] ****
  // [bpTypeName] => [bpTypeSource]
  let tmpTypeSource = result.name;

  // is array
  // check if it is a array
  // analyze if it is a array type
  let [isArray, arrayType] = parseArrayType(
    type.source,
    result.name,
    isReturnType,
    options
  );
  if (isArray) {
    tmpTypeSource = arrayType;
    result.isTArray = true;
  }

  // is a pointer
  // should be after parseArrayType
  let [needKeepPointer, pointerType] = parsePointerType(type, result.name);
  if (needKeepPointer) {
    tmpTypeSource = pointerType;

    // TBD(WinterPu) for now: [isPointer] doesn't influence [isTArray]
    result.isPointer = true;
  }

  let tmpDeclType = tmpTypeSource;
  let tmpDelegateType =
    data_bptype_conv?.bpDesignedTypeDelegate ?? tmpTypeSource;

  // is_const  /  isOutput
  // TBD(WinterPu)
  // 1. char* how to handle
  // 2. char** how to handle
  // 3. Set / Map ...
  if (isOutput !== undefined) {
    if (isOutput) {
      // isOutput 是 true
      tmpTypeSource = tmpTypeSource + ' &';

      // delegate type: if it is an output type: it cannot be without const, so keep delegateType as source without any qualifier
      // TBD(WinterPu)
    } else {
      // isOutput 是 false

      // TBD(WinterPu)
      // [X]delegate type: if it is not an output type: it would always be with const and &
      // tmpDelegateType = 'const ' + tmpTypeSource + ' &';

      // TBD(WinterPu)
      // Delegate Type should be the same as CBExecutor's function type
      // otherwise,  the DECLARE_DYNAMIC_MULTICAST_DELEGATE_XXXX would be invalid

      // const
      if (type.is_const) {
        tmpDelegateType = 'const ' + tmpTypeSource + ' &';
        tmpTypeSource = 'const ' + tmpTypeSource + ' &';
      }
    }
  } else {
    // const
    if (type.is_const) {
      tmpTypeSource = 'const ' + tmpTypeSource + ' &';
      tmpDelegateType = tmpTypeSource;
    }
  }

  // assign result
  result.source = data_bptype_conv?.bpDesignedTypeSource ?? tmpTypeSource;
  result.declType = data_bptype_conv?.bpDesignedDeclType ?? tmpDeclType;
  result.delegateType = tmpDelegateType;

  // **** Fourth Step: Get Conversion Function ****
  result.bpConv_BPFromCpp = genBPConvertFromRawType(type, result.isTArray);
  result.bpConv_CppFromBP = genBPConvertToRawType(type, result.isTArray);

  // **** Fifth Step: Get Conversion Decl Type ****
  // some types are different during decl type
  // default DeclType: is result.name

  let cppDeclTypeVal = type.name;

  // TBD(WinterPu)
  // it means: do we need [SetArray<RawType*> (RAW_TYPE)] or [SetArray<RawType>(RAW_TYPE*)]
  // some rules for decl type:
  // Ex. void -> void*
  if (result.isTArray) {
    cppDeclTypeVal = Tools.removeAttributes(type.source);
  }

  result.bpConvDeclTypeSPRule =
    data_bptype_conv?.declTypeSPRule ?? DeclTypeSPRule.DefaultNoSP;
  // special rule
  if (result.name === 'FString' && isOutput) {
    result.bpConvDeclTypeSPRule = DeclTypeSPRule.SP_String_Output_512;
  }

  result.cppDeclType = data_bptype_conv?.cppDesignedDeclType ?? cppDeclTypeVal;

  return result;
}

// struct - member variable: default value
export type BPDictInitializer = { [paramName: string]: ConstructorInitializer };

export function getBPMemberVariableDefaultValue(
  dictStructInitializer: BPDictInitializer,
  member_variable: MemberVariable,
  bpType: UEBPType
): [boolean, string] {
  let bNeedDefaultValue = false;
  let valDefaultVal = undefined;
  const data_bptype_conv = getBPTypeConvData(member_variable.type.source);

  // [Step 01]: Directly Assigned
  if (map_struct_member_variable_default_value[member_variable.fullName]) {
    valDefaultVal =
      map_struct_member_variable_default_value[member_variable.fullName];
    bNeedDefaultValue = true;
    return [bNeedDefaultValue, valDefaultVal];
  }

  // UStruct / UClass / TArray  no need default value
  if (
    bpType.isTArray ||
    bpType.declType.includes(AGORA_MUSTACHE_DATA.UEBP_PREFIX_STRUCT) ||
    bpType.declType.includes(AGORA_MUSTACHE_DATA.UEBP_PREFIX_CLASS)
  ) {
    bNeedDefaultValue = false;
    valDefaultVal = '';
    return [bNeedDefaultValue, valDefaultVal];
  }

  // TBD if there is no default constructor
  if (dictStructInitializer[member_variable.name]) {
    bNeedDefaultValue = true;
    // [TBD]
    valDefaultVal = dictStructInitializer[member_variable.name].values[0];

    let cpp_type = dictStructInitializer[member_variable.name]?.type;
    let cpp_type_without_namespace = Tools.convertTypeNameToNodeName(cpp_type);
    let enum_val = BPHelper.getMapCpp2BPEnum().get(cpp_type_without_namespace);
    if (enum_val) {
      valDefaultVal =
        `${AGORA_MUSTACHE_DATA.UABTEnum_WrapWithUE}(` +
        dictStructInitializer[member_variable.name].values[0] +
        ')';
      bNeedDefaultValue = true;
    }
  }

  // directly assigned: use type default value
  const tmpVal = data_bptype_conv?.defaultValue ?? undefined;
  if (tmpVal) {
    valDefaultVal = tmpVal;
    bNeedDefaultValue = true;
  }

  // Enum default value
  if (valDefaultVal === undefined) {
    let cpp_type_without_namespace = Tools.convertTypeNameToNodeName(
      member_variable.type.source
    );
    let enum_val = BPHelper.getMapCpp2BPEnum().get(cpp_type_without_namespace);
    if (enum_val) {
      const byType = member_variable.type.user_data.bpType;
      valDefaultVal = `static_cast<${byType.name}>(0)`;
      bNeedDefaultValue = true;
    }
  }

  // // Optional Value Remove Default Value
  // // this should already be included in the UCLASS Exempt.
  // if (valDefaultVal === undefined) {
  //   if (member_variable.type.name == 'Optional') {
  //     bNeedDefaultValue = false;
  //   }
  // }

  // TBD(WinterPu)
  // For Pointer Type
  // currently, have no idea about this situation.
  // need to check in the future
  if (valDefaultVal === undefined) {
    let [bNeedPointer, pointer_type] = parsePointerType(member_variable.type);
    Logger.Print(
      `${member_variable.type.source} getBPMemberVariableDefaultValue parsePointerType ${bNeedPointer} ${pointer_type}`
    );
    if (bNeedPointer) {
      bNeedDefaultValue = true;
      valDefaultVal = 'nullptr';
    }
  }

  if (valDefaultVal === undefined) {
    valDefaultVal = 'Unknown_TBD';
  }

  // TBD(WinterPu)
  // Special Case: FString
  // some fix
  if (bpType.declType === 'FString') {
    if (
      valDefaultVal === '0' ||
      valDefaultVal === 'NULL' ||
      valDefaultVal === 'nullptr'
    ) {
      valDefaultVal = '""';
    } else {
      valDefaultVal = `TEXT("${valDefaultVal}")`;
    }
  }

  if (bpType.declType === 'int64') {
    // For Android Compilation
    if (valDefaultVal === 'NULL') {
      valDefaultVal = '0';
    }
    // remove warnings
    if (bNeedDefaultValue == false) {
      bNeedDefaultValue = true;
      valDefaultVal = '0';
    }
  }

  return [bNeedDefaultValue, valDefaultVal];
}

export function getMethod_NativePtr(node_method: MemberFunction): string {
  return map_class_initialization[node_method.parent_name]?.NativePtr ?? '';
}

export type ClazzAddtionalContext = ClazzAddtionalContext_;
export function getContext_BPClass(clazz_name: string): ClazzAddtionalContext_ {
  return map_class_initialization[clazz_name];
}
