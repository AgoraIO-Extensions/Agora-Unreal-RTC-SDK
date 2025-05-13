import path from 'path';

import {
  CXXFile,
  CXXTYPE,
  CXXTerraNode,
  Clazz,
  MemberFunction,
  MemberVariable,
  SimpleType,
  Struct,
  Variable,
} from '@agoraio-extensions/cxx-parser';

import * as CppHelper from '../cpp_helper';
import * as FilterHelper from '../filter_helper';
import * as Logger from '../logger';

import * as Tools from '../tools';

import * as AgoraHelper from './agora_helper';
import {
  BPMethodContext,
  BPParamContext,
  BPStructContext,
} from './bpcontext_data';
import { map_includefiles } from './bpincludefiles_data';
import * as BPNameHelper from './bpname_helper';

import { BPNodeCategoryType } from './bpname_helper';
import {
  ConversionWayType,
  DeclTypeSPRule,
  map_bptype_conv_data,
  map_class_struct_without_default_constructor,
  map_decltype_special_rule,
  map_method_param_size_count,
  map_return_bptype_default_value,
  map_return_bptype_fix,
  map_return_context_default_value,
  map_struct_member_variable_size_count,
} from './bptype_data_conv';
import * as BPContextReplacedHelper from './bptype_data_replaced/helper';
import { ClazzMethodReplacedContext_ } from './bptype_data_replaced/helper';
import { UEBPType } from './bptype_helper';

import * as BPTypeHelper from './bptype_helper';
import { AGORA_MUSTACHE_DATA } from './bptype_mustache_data';

export function filterEmptyNameNode(node: CXXTerraNode): boolean {
  return node.__TYPE === CXXTYPE.Enumz && node.name === '';
}

// [Step 01]: About BP Include Files
export function getBPFileName(file_name: string): string {
  return BPNameHelper.genBPFileName(file_name);
}

export function getIncludeFilesForBP(cxxFile: CXXFile): string[] {
  let includeFiles: string[] = [];

  // Directly Assigned
  if (map_includefiles[cxxFile.fileName]) {
    return map_includefiles[cxxFile.fileName];
  }

  cxxFile.nodes.forEach((node: CXXTerraNode) => {
    if (node.__TYPE == CXXTYPE.IncludeDirective) {
      let inc_dir = node.asIncludeDirective();
      const filename = Tools.extractFileName(inc_dir.include_file_path) ?? '';
      if (mapFileName2BPName.has(filename)) {
        const bp_filename = mapFileName2BPName.get(filename) ?? '';
        const ext_name = path.extname(inc_dir.include_file_path);
        includeFiles.push(`#include "${bp_filename}${ext_name}"`);
      }
    }
  });
  return includeFiles;
}

// [Step 02]: About BP Name
const mapFileName2BPName: Map<string, string> = new Map();
const mapCpp2BPClass: Map<string, string> = new Map();
const mapCpp2BPStruct: Map<string, string> = new Map();
const mapCpp2BPEnum: Map<string, string> = new Map();

export function getMapFileName2BPName(): Map<string, string> {
  return mapFileName2BPName;
}

export function getMapCpp2BPClass(): Map<string, string> {
  return mapCpp2BPClass;
}

export function getMapCpp2BPStruct(): Map<string, string> {
  return mapCpp2BPStruct;
}

export function getMapCpp2BPEnum(): Map<string, string> {
  return mapCpp2BPEnum;
}

export function registerBPTypes(cxxfiles: CXXFile[]) {
  mapCpp2BPClass.clear();
  mapCpp2BPStruct.clear();
  mapCpp2BPEnum.clear();
  mapFileName2BPName.clear();

  cxxfiles.map((cxxfile: CXXFile) => {
    const fileName = CppHelper.getFileName(cxxfile);
    const bpFileName = BPNameHelper.genBPFileName(fileName);
    mapFileName2BPName.set(fileName, bpFileName);

    cxxfile.nodes.map((node) => {
      if (filterEmptyNameNode(node)) {
        return;
      }
      const key_registeredtype = BPNameHelper.getBPTypeRegisteredKey(node);
      // Only For Clazz
      if (node.__TYPE == CXXTYPE.Clazz) {
        const bp_name = BPNameHelper.genBPNodeName(
          key_registeredtype,
          BPNodeCategoryType.UClass
        );
        mapCpp2BPClass.set(key_registeredtype, bp_name);
      } else if (node.__TYPE == CXXTYPE.Struct) {
        // Only For Struct
        const bp_name = BPNameHelper.genBPNodeName(
          key_registeredtype,
          BPNodeCategoryType.UStruct
        );
        mapCpp2BPStruct.set(key_registeredtype, bp_name);
      } else if (node.__TYPE == CXXTYPE.Enumz) {
        // Only For Enumz
        const bp_name = BPNameHelper.genBPNodeName(
          key_registeredtype,
          BPNodeCategoryType.UEnum
        );
        mapCpp2BPEnum.set(key_registeredtype, bp_name);
      }
    });
  });

  registerBPNameForSelfDefinedType();
}

export function registerBPNameForSelfDefinedType() {
  // register some type you defined in conversion map
  // get custom defined bp types in conv map: Ex. FUABT_Opt_int
  // TBD(WinterPu)
  // For now, all custom defined bp types are structs
  for (const [typeName, typeData] of Object.entries(map_bptype_conv_data)) {
    if (typeData.isCustomBPType === true) {
      mapCpp2BPStruct.set(typeName, typeData.bpTypeName);
    }
  }
}

export function getBPName(node: CXXTerraNode): [CXXTYPE, string] {
  const key_registeredtype = BPNameHelper.getBPTypeRegisteredKey(node);
  let typeCategory = CXXTYPE.Unknown;
  let bpTypeName = key_registeredtype;

  if (mapCpp2BPClass.has(key_registeredtype)) {
    typeCategory = CXXTYPE.Clazz;
    bpTypeName = mapCpp2BPClass.get(key_registeredtype) ?? key_registeredtype;
  } else if (mapCpp2BPStruct.has(key_registeredtype)) {
    typeCategory = CXXTYPE.Struct;
    bpTypeName = mapCpp2BPStruct.get(key_registeredtype) ?? key_registeredtype;
  } else if (mapCpp2BPEnum.has(key_registeredtype)) {
    typeCategory = CXXTYPE.Enumz;
    bpTypeName = mapCpp2BPEnum.get(key_registeredtype) ?? key_registeredtype;
  }
  if (node.__TYPE === CXXTYPE.MemberFunction) {
    // For Callback Delegate: call [getBPMethodNameFullData]
    typeCategory = CXXTYPE.MemberFunction;
    const dataBPMethodName = BPNameHelper.genBPMethodName(
      node.asMemberFunction()
    );
    bpTypeName = dataBPMethodName.methodName;
  }
  return [typeCategory, bpTypeName];
}

export function genContext_BPMethodReplacedDecl(
  node_method: MemberFunction
): ClazzMethodReplacedContext_ {
  const map_data = BPContextReplacedHelper.getMapDataMethodReplacedContext();
  const replaced_data = map_data[node_method.fullName];
  return (
    replaced_data ?? {
      doReplceDecl: false,
      decl: ``,
      doReplceImpl: false,
      impl: ``,
    }
  );
}

export function getBPMethodNameFullData(
  node_method: MemberFunction,
  isCallback: boolean
): BPNameHelper.BPMethodName {
  return BPNameHelper.genBPMethodName(node_method, isCallback);
}

// [Step 03]: About BP Type
export function getBPType(type: SimpleType): UEBPType {
  return BPTypeHelper.convertToBPType(type);
}

export function genBPReturnType(return_type: SimpleType): string {
  let isReturnType = true;
  let options: BPTypeHelper.AnalysisOptions = {
    isAgoraType: AgoraHelper.isAgoraClassType(return_type),
  };

  const bp_type = BPTypeHelper.convertToBPType(
    return_type,
    undefined,
    isReturnType,
    options
  );

  let result = bp_type.declType;
  if (map_return_bptype_fix[result]) {
    result = map_return_bptype_fix[result];
  }
  return result;
}

export function genBPParameterType(param: Variable): UEBPType {
  // char* => FString
  // in method it would be an output param
  return BPTypeHelper.convertToBPType(param.type, param.is_output);
}

// [Step 04]: About BP default Value
export function prepareBPStructInitializerDict(
  node_struct: Struct
): BPTypeHelper.BPDictInitializer {
  const dict_variable_initializer: BPTypeHelper.BPDictInitializer = {};

  node_struct.constructors.map((constructor, index) => {
    if (constructor.parameters.length == 0) {
      //default constructor
      constructor.initializerList.map((initializer) => {
        dict_variable_initializer[initializer.name] = initializer;
      });
    }
  });

  return dict_variable_initializer;
}

export function getBPStructData_DefaultVal(
  dict_variable_initializer: BPTypeHelper.BPDictInitializer,
  member_variable: MemberVariable,
  bpType: UEBPType
): string {
  let bNeedDefaultVal = false;
  let defaultVal = '';
  let outputfomatDefaultVal = '';

  [bNeedDefaultVal, defaultVal] = BPTypeHelper.getBPMemberVariableDefaultValue(
    dict_variable_initializer,
    member_variable,
    bpType
  );

  // TBD(WinterPu) some default values are not matched with UE Type
  // Ex. FString Var = 0;

  if (bNeedDefaultVal) {
    outputfomatDefaultVal = `= ${defaultVal}`;
  }

  return outputfomatDefaultVal;
}

// [Step 05]: About BP Context
export function genContext_BPStruct(
  node_struct: Struct,
  prefix_indent: string = ''
): BPStructContext {
  let contextConstructor = '';
  let contextCreateRawData = '';
  let contextFreeRawData = '';

  const addOneLineFunc = function (line: string): string {
    return Tools.addOneLine_Format(line, prefix_indent);
  };

  // [Step 01] Begin
  // Ex. {{{fullName}}} AgoraData;
  if (map_class_struct_without_default_constructor[node_struct.fullName]) {
    contextCreateRawData += addOneLineFunc(
      `${map_class_struct_without_default_constructor[node_struct.fullName]}`
    );
  } else {
    contextCreateRawData += addOneLineFunc(
      `${node_struct.fullName} ${AGORA_MUSTACHE_DATA.AGORA_DATA};`
    );
  }

  node_struct.member_variables.map((member_variable, index) => {
    let type = member_variable.type;
    let struct_full_name = member_variable?.parent?.fullName ?? '';
    let bpType = BPTypeHelper.convertToBPType(type);
    const cpp_decl_type = bpType.cppDeclType;
    const var_SizeCount = getBPSizeCount(node_struct, member_variable);
    const conv_bpfromcpp = bpType.bpConv_BPFromCpp;
    const conv_cppfrombp = bpType.bpConv_CppFromBP;
    const macro_scope_start =
      CppHelper.createCompilationDirectivesContent(member_variable);
    const macro_scope_end = CppHelper.createCompilationDirectivesContent(
      member_variable,
      false
    );
    if (
      Tools.IsNotEmptyStr(macro_scope_start) &&
      Tools.IsNotEmptyStr(macro_scope_end)
    ) {
      contextConstructor += addOneLineFunc(`${macro_scope_start}`);
      contextCreateRawData += addOneLineFunc(`${macro_scope_start}`);
    }

    // **** Constructor Context ****

    const str_constructor_context = genContextBasedOnConversionWayType(
      EBPContextGenType.Struct_Constructor,
      member_variable,
      bpType,
      conv_bpfromcpp.convFuncType,
      undefined,
      var_SizeCount,
      ''
    );
    contextConstructor += addOneLineFunc(str_constructor_context);

    // **** CreateRawData Context ****
    const str_create_raw_data_context = genContextBasedOnConversionWayType(
      EBPContextGenType.Struct_CreateRawData,
      member_variable,
      bpType,
      conv_cppfrombp.convFuncType,
      undefined,
      var_SizeCount,
      ''
    );
    contextCreateRawData += addOneLineFunc(str_create_raw_data_context);

    // **** FreeRawData Context ****
    const tmpContextFreeRawData = genContextBasedOnConversionWayType(
      EBPContextGenType.Struct_FreeRawData,
      member_variable,
      bpType,
      conv_cppfrombp.convFuncType,
      undefined,
      var_SizeCount,
      ''
    );

    if (
      Tools.IsNotEmptyStr(macro_scope_start) &&
      Tools.IsNotEmptyStr(macro_scope_end)
    ) {
      contextConstructor += addOneLineFunc(`${macro_scope_end}`);
      contextCreateRawData += addOneLineFunc(`${macro_scope_end}`);
      if (tmpContextFreeRawData && tmpContextFreeRawData !== '') {
        contextFreeRawData += addOneLineFunc(`${macro_scope_start}`);
      }
    }
    if (tmpContextFreeRawData && tmpContextFreeRawData !== '') {
      contextFreeRawData += addOneLineFunc(tmpContextFreeRawData);

      if (
        Tools.IsNotEmptyStr(macro_scope_start) &&
        Tools.IsNotEmptyStr(macro_scope_end)
      ) {
        contextFreeRawData += addOneLineFunc(`${macro_scope_end}`);
      }
    }
  });

  // Ex. return AgoraData;
  contextCreateRawData += addOneLineFunc(
    `return ${AGORA_MUSTACHE_DATA.AGORA_DATA};`
  );

  const result = new BPStructContext();
  result.contextConstructor = contextConstructor;
  result.contextCreateRawData = contextCreateRawData;
  result.contextFreeRawData = contextFreeRawData;

  return result;
}

function genContext_ConvDeclType(
  param: Variable,
  bpType: UEBPType,
  bIsCppFromBP: boolean,
  extra_SizeCount?: string
): BPParamContext {
  extra_SizeCount = extra_SizeCount ?? '';
  const prefix_var_name = bIsCppFromBP
    ? AGORA_MUSTACHE_DATA.RAW_
    : AGORA_MUSTACHE_DATA.UEBP_;
  const param_name = param.name;
  const decl_var_name = prefix_var_name + param_name;

  const addOneLineFunc = function (line: string): string {
    return Tools.addOneLine_Format(line, '');
  };

  const data_conv = bIsCppFromBP
    ? bpType.bpConv_CppFromBP
    : bpType.bpConv_BPFromCpp;
  const decl_type = bIsCppFromBP ? bpType.cppDeclType : bpType.declType;

  let result = new BPParamContext();
  // Default: DeclType A = B;
  result.contextDecl = `${decl_type} ${decl_var_name} = ${param_name};`;
  result.contextUsage = `${decl_var_name}`;
  result.contextFree = '';

  // [Step 01]: if it has special rule, directly use it
  if (bpType.bpConvDeclTypeSPRule !== DeclTypeSPRule.DefaultNoSP) {
    const full_data_rule = map_decltype_special_rule.get(
      bpType.bpConvDeclTypeSPRule
    );
    const data_rule = bIsCppFromBP
      ? full_data_rule?.CppFromBP
      : full_data_rule?.BPFromCpp;
    if (data_rule) {
      result.contextDecl = `${data_rule.funcDecl(decl_var_name, param_name)}`;
      result.contextUsage = `${data_rule.funcUsage(decl_var_name)}`;
      result.contextFree = `${data_rule.funcFree(
        bpType.name,
        decl_var_name,
        param_name
      )}`;
    }
  } else if (data_conv.convFuncType !== ConversionWayType.NoNeedConversion) {
    // [Step 02]: Use Default Basic Conversion
    const convWayType = data_conv.convFuncType;

    // [Part - Decl]
    const str_decl = genContextBasedOnConversionWayType(
      EBPContextGenType.DeclType_Decl,
      param,
      bpType,
      convWayType,
      bIsCppFromBP,
      '',
      extra_SizeCount
    );
    result.contextDecl = addOneLineFunc(str_decl);

    // [Part - Usage]
    const str_usage = genContextBasedOnConversionWayType(
      EBPContextGenType.DeclType_Usage,
      param,
      bpType,
      convWayType,
      bIsCppFromBP,
      '',
      extra_SizeCount
    );
    result.contextUsage = str_usage;

    // [Part - Free]
    const str_free = genContextBasedOnConversionWayType(
      EBPContextGenType.DeclType_Free,
      param,
      bpType,
      convWayType,
      bIsCppFromBP,
      '',
      extra_SizeCount
    );
    if (Tools.IsNotEmptyStr(str_free)) {
      result.contextFree = addOneLineFunc(str_free);
    }
  }

  return result;
}

function genContext_BPMethodReturnValBegin(
  return_type: SimpleType,
  prefix_indent: string = ''
): string {
  const addOneLineFunc = function (line: string): string {
    return Tools.addOneLine_Format(line, prefix_indent);
  };

  let return_type_bytype = BPTypeHelper.convertToBPType(return_type);
  const bpTypeConvData = BPTypeHelper.getBPTypeConvData(return_type.source);

  let decl_type = return_type_bytype.declType;

  // should be default value not a failed value.
  let defaultVal =
    bpTypeConvData?.defaultBPValue ??
    map_return_context_default_value[decl_type] ?? // ref bp
    map_return_bptype_default_value[return_type.source] ?? // ref cpp
    '';

  if (Tools.IsNotEmptyStr(defaultVal)) {
    defaultVal = `= ${defaultVal}`;
  } else {
    defaultVal = '';
  }

  let result = addOneLineFunc(
    `${decl_type} ${AGORA_MUSTACHE_DATA.FINAL_RETURN_RESULT} ${defaultVal};`
  );
  return result;
}

function genContext_BPMethodReturnVal(
  return_type: SimpleType,
  prefix_indent: string = ''
): string {
  const bpType = BPTypeHelper.convertToBPType(return_type);
  const addOneLineFunc = function (line: string): string {
    return Tools.addOneLine_Format(line, prefix_indent);
  };
  // [Step 02]: Use Default Basic Conversion
  const convWayType = bpType.bpConv_BPFromCpp.convFuncType;

  // [Part - Decl]
  // TBD(WinterPu)
  // for some return val: Ex. EnumerateVideoDevices
  // TArray<FUABT_VideoDeviceInfo> ReturnVal; UABT::SetBPDataArray<agora::rtc::ext::VideoDeviceInfo, FUABT_VideoDeviceInfo>(ReturnVal, ret, );
  // for now, we set 1 as the default size count
  const str_decl = genContextBasedOnConversionWayType(
    EBPContextGenType.DeclType_Decl,
    undefined,
    bpType,
    convWayType,
    false,
    '1',
    '1',
    AGORA_MUSTACHE_DATA.RETURN_VAL,
    AGORA_MUSTACHE_DATA.RETURN_VAL_DECL
  );
  let result = addOneLineFunc(str_decl);
  result += addOneLineFunc(
    `${AGORA_MUSTACHE_DATA.FINAL_RETURN_RESULT} =  ${AGORA_MUSTACHE_DATA.RETURN_VAL_DECL};`
  );
  return result;
}

export function genContext_BPMethod(
  node_method: MemberFunction,
  prefix_indent: string = ''
): BPMethodContext {
  const addOneLineFunc = function (line: string): string {
    return Tools.addOneLine_Format(line, prefix_indent);
  };

  // Example:

  // decl: std::string a = TCHAR_TO_UTF8(*b);
  // usage: a.c_str();
  // free: none
  let contextParam_BPFromCpp = new BPParamContext();

  // decl: FString a = UTF8_TO_TCHAR(b);
  // usage: a;
  // free: none
  let contextParam_CppFromBP = new BPParamContext();

  let result = new BPMethodContext();

  node_method.parameters.map((param, index) => {
    const bptype = genBPParameterType(param);
    const extra_SizeCount = getBPSizeCount(node_method, param);

    contextParam_BPFromCpp = genContext_ConvDeclType(
      param,
      bptype,
      false,
      extra_SizeCount
    );

    contextParam_CppFromBP = genContext_ConvDeclType(
      param,
      bptype,
      true,
      extra_SizeCount
    );

    // Usage
    const param_delimiter =
      index == node_method.parameters.length - 1 ? '' : ', ';

    // BP From Cpp
    // Decl
    result.contextParam_BPFromCpp.contextDecl += addOneLineFunc(
      contextParam_BPFromCpp.contextDecl
    );

    // Usage
    result.contextParam_BPFromCpp.contextUsage += `${contextParam_BPFromCpp.contextUsage}${param_delimiter}`;

    // Free
    result.contextParam_BPFromCpp.contextFree += addOneLineFunc(
      contextParam_BPFromCpp.contextFree
    );

    // Cpp From BP
    // Decl
    result.contextParam_CppFromBP.contextDecl += addOneLineFunc(
      contextParam_CppFromBP.contextDecl
    );

    // Usage
    result.contextParam_CppFromBP.contextUsage += `${contextParam_CppFromBP.contextUsage}${param_delimiter}`;

    // Free
    result.contextParam_CppFromBP.contextFree += addOneLineFunc(
      contextParam_CppFromBP.contextFree
    );
  });

  // TBD(WinterPu)
  // return type's conversion

  // TBD(WinterPu):
  // Need to Remove FilterHelper
  // Optimize [genBPReturnType]
  result.contextReturnValBegin = genContext_BPMethodReturnValBegin(
    node_method.return_type,
    prefix_indent
  );

  // it may has multiple lines:
  // so put addOneLineFunc inside the function
  result.contextReturnValSetVal = genContext_BPMethodReturnVal(
    node_method.return_type,
    prefix_indent
  );

  result.contextReturnValEnd = addOneLineFunc(
    `return ${AGORA_MUSTACHE_DATA.FINAL_RETURN_RESULT};`
  );
  return result;
}

export function genContext_BPMethod_NativePtr(
  node_method: MemberFunction,
  prefix_indent: string = ''
): string {
  return BPTypeHelper.getMethod_NativePtr(node_method);
}

export function genContext_BPClass(
  node_clazz: Clazz,
  prefix_indent: string = ''
): BPTypeHelper.ClazzAddtionalContext {
  // TBD(WinterPu):
  // 1. Impl prefix_indent
  return BPTypeHelper.getContext_BPClass(node_clazz.name);
}

export function getBPSizeCount(
  node: Struct | MemberFunction,
  target_member_var: MemberVariable | Variable
): string {
  const type = node.__TYPE;
  if (type === CXXTYPE.Struct) {
    const node_struct = node.asStruct();

    const tar_var_name = target_member_var.name;

    if (target_member_var.fullName in map_struct_member_variable_size_count) {
      return map_struct_member_variable_size_count[target_member_var.fullName];
    }

    for (const one_var of node_struct.member_variables) {
      if (
        one_var.name == tar_var_name + 'Size' ||
        one_var.name == tar_var_name + 'Count' ||
        one_var.name == tar_var_name + 'Num'
      ) {
        return one_var.name;
      }
    }
  } else if (type === CXXTYPE.MemberFunction) {
    const node_method = node.asMemberFunction();

    const tar_var_name = target_member_var.name;

    if (target_member_var.fullName in map_method_param_size_count) {
      return map_method_param_size_count[target_member_var.fullName];
    }

    for (const one_var of node_method.parameters) {
      if (
        one_var.name == tar_var_name + 'Size' ||
        one_var.name == tar_var_name + 'Count' ||
        one_var.name == tar_var_name + 'Num'
      ) {
        return one_var.name;
      }
    }
  }

  const type_size_count = Tools.extractBracketNumber(
    target_member_var.type.source
  );

  if (Tools.IsNotEmptyStr(type_size_count)) {
    return type_size_count;
  }

  Logger.PrintError(
    `Unknown size count variable for ${target_member_var.fullName}`
  );

  // TBD(WinterPu):
  // FUABT_ChannelMediaRelayConfiguration.srcInfo should be pointer rather than array
  // Ex.
  // ScreenCaptureParameters.excludeWindowList should be excludeWindowCount
  return '1';
}

export enum EBPContextGenType {
  Struct_Constructor, // BP = Cpp
  Struct_CreateRawData, // Cpp = BP
  Struct_FreeRawData, // Cpp = BP
  DeclType_Decl, // BP = Cpp & Cpp = BP
  DeclType_Usage, // BP = Cpp & Cpp = BP
  DeclType_Free, // BP = Cpp & Cpp = BP
}

export function genContextBasedOnConversionWayType(
  context_type: EBPContextGenType,
  variable: Variable | MemberVariable | undefined,

  // data
  bpType: UEBPType,
  conv_way_type: ConversionWayType,

  extra_data_bIsCppFromBP: boolean | undefined,
  extra_data_size_count: string,
  extra_data_decl_size_count: string,
  extra_data_designed_var_name?: string,
  extra_data_designed_decl_var_name?: string,
  extra_data?: any
): string {
  function extractArraySizeFromType(bpType: UEBPType) {
    return Tools.extractBracketNumber(bpType.source);
  }

  function genSizeVarStr(str_array_size: string, prefix: string): string {
    return Tools.isNumeric(str_array_size)
      ? str_array_size
      : prefix + str_array_size;
  }

  // common data
  const conv_bpfromcpp = bpType.bpConv_BPFromCpp;
  const conv_cppfrombp = bpType.bpConv_CppFromBP;
  const var_name = extra_data_designed_var_name ?? variable?.name;

  // for struct
  const AGORA_DATA = AGORA_MUSTACHE_DATA.AGORA_DATA;
  const s_cpp_decl_type = bpType.cppDeclType;
  const s_cpp_type_name = bpType.cppTypeName;
  const s_bp_decl_type = bpType.declType;
  const s_bp_type_name = bpType.name;
  const conv_array_size = extra_data_size_count;

  // decl type
  if (
    extra_data_bIsCppFromBP === undefined &&
    (context_type === EBPContextGenType.DeclType_Decl ||
      context_type === EBPContextGenType.DeclType_Usage ||
      context_type === EBPContextGenType.DeclType_Free)
  ) {
    Logger.PrintError(
      `bIsCppFromBP is undefined for ${
        extra_data_designed_var_name ?? variable?.fullName ?? 'unknown'
      }`
    );
  }

  const isCppFromBP = extra_data_bIsCppFromBP;
  //TBD(WinterPu)
  // get rid of:
  // Ex. UABT::New_RawDataArray<agora::rtc::uid_t, TArray<int64>>();
  const decl_type = isCppFromBP ? bpType.cppDeclType : bpType.declType;
  const tmpl_raw_decl_type_name = bpType.cppTypeName;
  const tmpl_bp_convtodecl_type_name = bpType.name;
  const prefix_var_name = isCppFromBP
    ? AGORA_MUSTACHE_DATA.RAW_
    : AGORA_MUSTACHE_DATA.UEBP_;
  let decl_var_name = prefix_var_name + var_name;
  if (extra_data_designed_decl_var_name) {
    decl_var_name = extra_data_designed_decl_var_name;
  }
  const data_decl_conv = isCppFromBP ? conv_cppfrombp : conv_bpfromcpp;
  let decl_array_size =
    extra_data_decl_size_count ?? extractArraySizeFromType(bpType);

  const STR_INVALID_CONV = 'Invalid Conversion';
  const declIsCppFromBP = function (res: string): string {
    return isCppFromBP ? res : STR_INVALID_CONV;
  };

  const declIsBPFromCpp = function (res: string): string {
    return isCppFromBP ? STR_INVALID_CONV : res;
  };

  const defaultTmpl_AllInValidConv: Record<EBPContextGenType, string> = {
    [EBPContextGenType.Struct_Constructor]: STR_INVALID_CONV,
    [EBPContextGenType.Struct_CreateRawData]: STR_INVALID_CONV,
    [EBPContextGenType.Struct_FreeRawData]: STR_INVALID_CONV,
    [EBPContextGenType.DeclType_Decl]: STR_INVALID_CONV,
    [EBPContextGenType.DeclType_Usage]: STR_INVALID_CONV,
    [EBPContextGenType.DeclType_Free]: STR_INVALID_CONV,
  };

  const defaultTmpl_NoConv: Record<EBPContextGenType, string> = {
    [EBPContextGenType.Struct_Constructor]: `this->${var_name} = ${AGORA_DATA}.${var_name};`,
    [EBPContextGenType.Struct_CreateRawData]: `${AGORA_DATA}.${var_name} = this->${var_name};`,
    [EBPContextGenType.Struct_FreeRawData]: '',
    [EBPContextGenType.DeclType_Decl]: `${decl_type} ${decl_var_name} = ${var_name};`,
    [EBPContextGenType.DeclType_Usage]: `${decl_var_name}`,
    [EBPContextGenType.DeclType_Free]: '',
  };

  const genfunc_DefaultTmpl_BasicConv = function (
    bpfromcpp_conv_func: string,
    cppfrombp_conv_func: string,
    dec_conv_func: string
  ): Record<EBPContextGenType, string> {
    const result: Record<EBPContextGenType, string> = {
      [EBPContextGenType.Struct_Constructor]: `this->${var_name} = ${bpfromcpp_conv_func}(${AGORA_DATA}.${var_name});`,
      [EBPContextGenType.Struct_CreateRawData]: `${AGORA_DATA}.${var_name} = ${cppfrombp_conv_func}(this->${var_name});`,
      [EBPContextGenType.Struct_FreeRawData]: '',
      [EBPContextGenType.DeclType_Decl]: `${decl_type} ${decl_var_name} = ${dec_conv_func}(${var_name});`,
      [EBPContextGenType.DeclType_Usage]: `${decl_var_name}`,
      [EBPContextGenType.DeclType_Free]: '',
    };
    return result;
  };

  type TmplOptions = {
    bUseSize: boolean;
    bUseTmplType: boolean;
  };

  const genfunc_DefaultTmpl_SetArrayData = function (
    options: TmplOptions,
    conv_func_setdata_bpfromcpp: string,
    conv_func_setdata_cppfrombp: string,
    decl_func_setdata: string
  ): Record<EBPContextGenType, string> {
    const str_conv_array_size_bpfromcpp = options.bUseSize
      ? ', ' + genSizeVarStr(conv_array_size, `${AGORA_DATA}.`)
      : '';

    const str_conv_array_size_cppfrombp = options.bUseSize
      ? ', ' + genSizeVarStr(conv_array_size, `this->`)
      : '';

    const str_decl_array_size = options.bUseSize ? ', ' + decl_array_size : '';

    const str_conv_tmpl_type = options.bUseTmplType
      ? `<${s_cpp_type_name}, ${s_bp_type_name}>`
      : '';
    const str_decl_tmpl_type = options.bUseTmplType
      ? `<${tmpl_raw_decl_type_name}, ${tmpl_bp_convtodecl_type_name}>`
      : '';

    const result = {
      ...defaultTmpl_NoConv,
      [EBPContextGenType.Struct_Constructor]: `${conv_func_setdata_bpfromcpp}${str_conv_tmpl_type}(this->${var_name}, ${AGORA_DATA}.${var_name}${str_conv_array_size_bpfromcpp});`,
      [EBPContextGenType.Struct_CreateRawData]: `${conv_func_setdata_cppfrombp}(${AGORA_DATA}.${var_name},this->${var_name}${str_conv_array_size_cppfrombp});`,
      [EBPContextGenType.Struct_FreeRawData]: '',
      [EBPContextGenType.DeclType_Decl]: `${decl_type} ${decl_var_name}; ${decl_func_setdata}${str_decl_tmpl_type}(${decl_var_name}, ${var_name}${str_decl_array_size});`,
      [EBPContextGenType.DeclType_Usage]:
        defaultTmpl_NoConv[EBPContextGenType.DeclType_Usage],
      [EBPContextGenType.DeclType_Free]:
        defaultTmpl_NoConv[EBPContextGenType.DeclType_Free],
    };

    return result;
  };

  const genfunc_DefaultTmpl_CppFromBP_NewFreeData = function (
    options: TmplOptions,
    conv_func_new?: string,
    conv_func_free?: string,
    decl_func_new?: string,
    decl_func_free?: string
  ): Record<EBPContextGenType, string> {
    const str_conv_func_new = conv_func_new ?? conv_cppfrombp.convFunc;
    const str_conv_func_free =
      conv_func_free ?? conv_cppfrombp.convFuncAdditional01;
    const str_decl_func_new = decl_func_new ?? data_decl_conv.convFunc;
    const str_decl_func_free =
      decl_func_free ?? data_decl_conv.convFuncAdditional01;

    const str_conv_array_size = options.bUseSize
      ? ', ' + genSizeVarStr(conv_array_size, 'this->')
      : '';
    const str_decl_array_size = options.bUseSize ? ', ' + decl_array_size : '';

    const str_conv_tmpl_type = options.bUseTmplType
      ? `<${s_cpp_type_name}, ${s_bp_type_name}>`
      : '';
    const str_decl_tmpl_type = options.bUseTmplType
      ? `<${tmpl_raw_decl_type_name}, ${tmpl_bp_convtodecl_type_name}>`
      : '';

    const result: Record<EBPContextGenType, string> = {
      [EBPContextGenType.Struct_Constructor]: STR_INVALID_CONV,
      [EBPContextGenType.Struct_CreateRawData]: `${AGORA_DATA}.${var_name} = ${str_conv_func_new}${str_conv_tmpl_type}(this->${var_name}${str_conv_array_size});`,
      [EBPContextGenType.Struct_FreeRawData]: `${str_conv_func_free}${str_conv_tmpl_type}(${AGORA_DATA}.${var_name}${str_conv_array_size});`,
      [EBPContextGenType.DeclType_Decl]: declIsCppFromBP(
        `${decl_type} ${decl_var_name} = ${str_decl_func_new}${str_decl_tmpl_type}(${var_name}${str_decl_array_size});`
      ),
      [EBPContextGenType.DeclType_Usage]: declIsCppFromBP(`${decl_var_name}`),
      [EBPContextGenType.DeclType_Free]: declIsCppFromBP(
        `${str_decl_func_free}${str_decl_tmpl_type}(${decl_var_name}${str_decl_array_size});`
      ),
    };

    return result;
  };

  const genfunc_DefaultTmpl_CppFromBP_NewFreeArrayData = function (
    options: TmplOptions,
    conv_func_new?: string,
    conv_func_free?: string,
    decl_func_new?: string,
    decl_func_free?: string
  ): Record<EBPContextGenType, string> {
    const defaultTmpl_NewFreeConv = genfunc_DefaultTmpl_CppFromBP_NewFreeData(
      options,
      conv_func_new,
      conv_func_free,
      decl_func_new,
      decl_func_free
    );

    const str_conv_func_new = conv_func_new ?? conv_cppfrombp.convFunc;
    const str_conv_func_free =
      conv_func_free ?? conv_cppfrombp.convFuncAdditional01;
    const str_decl_func_new = decl_func_new ?? data_decl_conv.convFunc;
    const str_decl_func_free =
      decl_func_free ?? data_decl_conv.convFuncAdditional01;

    const str_conv_array_size = options.bUseSize
      ? ', ' + genSizeVarStr(conv_array_size, 'this->')
      : '';
    const str_decl_array_size = options.bUseSize ? ', ' + decl_array_size : '';

    const str_conv_tmpl_type = options.bUseTmplType
      ? `<${s_cpp_type_name}, ${s_bp_type_name}>`
      : '';
    const str_decl_tmpl_type = options.bUseTmplType
      ? `<${tmpl_raw_decl_type_name}, ${tmpl_bp_convtodecl_type_name}>`
      : '';

    // TBD(WinterPu);
    // it has bug:
    // Ex. for New_RawDataArray, [DeclType_Decl]
    // agora::rtc::uid_t* Raw_uidList = nullptr; UABT::New_RawDataArray<agora::rtc::uid_t, TArray<int64>>(Raw_uidList,uidList,1);
    // the pointer has not been memory allocated.
    const result: Record<EBPContextGenType, string> = {
      ...defaultTmpl_NewFreeConv,
      [EBPContextGenType.Struct_CreateRawData]: `${str_conv_func_new}${str_conv_tmpl_type}(${AGORA_DATA}.${var_name},this->${var_name}${str_conv_array_size});`,
      [EBPContextGenType.Struct_FreeRawData]: `${str_conv_func_free}${str_conv_tmpl_type}(${AGORA_DATA}.${var_name}${str_conv_array_size});`,
      [EBPContextGenType.DeclType_Decl]: declIsCppFromBP(
        `${decl_type} ${decl_var_name} = nullptr; ${str_decl_func_new}${str_decl_tmpl_type}(${decl_var_name},${var_name}${str_decl_array_size});`
      ),
      [EBPContextGenType.DeclType_Free]: declIsCppFromBP(
        `${str_decl_func_free}${str_decl_tmpl_type}(${decl_var_name}${str_decl_array_size});`
      ),
    };
    return result;
  };

  const genfunc_DefaultTmpl_CallConvFunc = function (
    conv_func_create: string,
    conv_func_free: string,
    decl_func_create: string,
    decl_func_free: string
  ): Record<EBPContextGenType, string> {
    const result = {
      ...defaultTmpl_NoConv,
      [EBPContextGenType.Struct_Constructor]: STR_INVALID_CONV,
      [EBPContextGenType.Struct_CreateRawData]: `${AGORA_DATA}.${var_name} = ${var_name}.${conv_func_create}();`,
      [EBPContextGenType.Struct_FreeRawData]: `${var_name}.${conv_func_free}(${AGORA_DATA}.${var_name});`,
      [EBPContextGenType.DeclType_Decl]: declIsCppFromBP(
        `${decl_type} ${decl_var_name} = ${var_name}.${decl_func_create}();`
      ),
      [EBPContextGenType.DeclType_Usage]: declIsCppFromBP(
        defaultTmpl_NoConv[EBPContextGenType.DeclType_Usage]
      ),
      [EBPContextGenType.DeclType_Free]: declIsCppFromBP(
        `${var_name}.${decl_func_free}(${decl_var_name});`
      ),
    };

    return result;
  };

  let result_map: Record<EBPContextGenType, string> = defaultTmpl_NoConv;

  switch (conv_way_type) {
    case ConversionWayType.NoNeedConversion:
      result_map = defaultTmpl_NoConv;
      break;
    case ConversionWayType.BasicConvFunc: {
      const conv_func_bpfromcpp = conv_bpfromcpp.convFunc;
      const conv_func_cppfrombp = conv_cppfrombp.convFunc;
      const conv_func_decl = data_decl_conv.convFunc;
      result_map = genfunc_DefaultTmpl_BasicConv(
        conv_func_bpfromcpp,
        conv_func_cppfrombp,
        conv_func_decl
      );
      break;
    }

    case ConversionWayType.DirectlyConv_StaticCast: {
      const conv_func_bpfromcpp = `static_cast<${s_bp_decl_type}>`;
      const conv_func_cppfrombp = `static_cast<${s_cpp_decl_type}>`;
      const conv_func_decl = `static_cast<${decl_type}>`;
      result_map = genfunc_DefaultTmpl_BasicConv(
        conv_func_bpfromcpp,
        conv_func_cppfrombp,
        conv_func_decl
      );
      break;
    }
    case ConversionWayType.DirectlyConv_ReinterpretCast: {
      const conv_func_bpfromcpp = `reinterpret_cast<${s_bp_decl_type}>`;
      const conv_func_cppfrombp = `reinterpret_cast<${s_cpp_decl_type}>`;
      const conv_func_decl = `reinterpret_cast<${decl_type}>`;
      result_map = genfunc_DefaultTmpl_BasicConv(
        conv_func_bpfromcpp,
        conv_func_cppfrombp,
        conv_func_decl
      );
      break;
    }

    case ConversionWayType.BPFromCpp_FString: {
      const conv_func = conv_bpfromcpp.convFunc;
      const decl_func = data_decl_conv.convFunc;
      result_map = {
        ...defaultTmpl_AllInValidConv,
        [EBPContextGenType.Struct_Constructor]: `this->${var_name} = ${conv_func}(${AGORA_DATA}.${var_name});`,
        [EBPContextGenType.Struct_CreateRawData]: STR_INVALID_CONV,
        [EBPContextGenType.Struct_FreeRawData]: STR_INVALID_CONV,
        [EBPContextGenType.DeclType_Decl]: `${decl_type} ${decl_var_name} = ${conv_func}(${var_name});`,
        [EBPContextGenType.DeclType_Usage]: `${decl_var_name}`,
        [EBPContextGenType.DeclType_Free]: '',
      };
      break;
    }

    case ConversionWayType.BPFromCpp_Func_SetBPDataArray: {
      const conv_func_setdata_bpfromcpp = AGORA_MUSTACHE_DATA.SET_BP_ARRAY_DATA;
      const conv_func_setdata_cppfrombp = AGORA_MUSTACHE_DATA.SET_BP_ARRAY_DATA;
      const decl_func = AGORA_MUSTACHE_DATA.SET_BP_ARRAY_DATA;
      result_map = genfunc_DefaultTmpl_SetArrayData(
        { bUseSize: true, bUseTmplType: true },
        conv_func_setdata_bpfromcpp,
        conv_func_setdata_cppfrombp,
        decl_func
      );
      break;
    }

    case ConversionWayType.SetArrayData: {
      const conv_func_setdata_bpfromcpp = conv_bpfromcpp.convFunc;
      const conv_func_setdata_cppfrombp = conv_cppfrombp.convFunc;
      const decl_func = data_decl_conv.convFunc;
      result_map = genfunc_DefaultTmpl_SetArrayData(
        { bUseSize: false, bUseTmplType: false },
        conv_func_setdata_bpfromcpp,
        conv_func_setdata_cppfrombp,
        decl_func
      );
      break;
    }

    case ConversionWayType.SetArrayData_Size: {
      const conv_func_setdata_bpfromcpp = conv_bpfromcpp.convFunc;
      const conv_func_setdata_cppfrombp = conv_cppfrombp.convFunc;
      const decl_func = data_decl_conv.convFunc;
      result_map = genfunc_DefaultTmpl_SetArrayData(
        { bUseSize: true, bUseTmplType: false },
        conv_func_setdata_bpfromcpp,
        conv_func_setdata_cppfrombp,
        decl_func
      );
      break;
    }

    case ConversionWayType.SetArrayData_Size_TmplType: {
      const conv_func_setdata_bpfromcpp = conv_bpfromcpp.convFunc;
      const conv_func_setdata_cppfrombp = conv_cppfrombp.convFunc;
      const decl_func = data_decl_conv.convFunc;
      result_map = genfunc_DefaultTmpl_SetArrayData(
        { bUseSize: true, bUseTmplType: true },
        conv_func_setdata_bpfromcpp,
        conv_func_setdata_cppfrombp,
        decl_func
      );
      break;
    }

    case ConversionWayType.CppFromBP_NewFreeData_CustomConvFunc: {
      result_map = genfunc_DefaultTmpl_CppFromBP_NewFreeData({
        bUseSize: false,
        bUseTmplType: false,
      });
      break;
    }

    case ConversionWayType.CppFromBP_NewFreeDataWithSize_CustomConvFunc: {
      result_map = genfunc_DefaultTmpl_CppFromBP_NewFreeData({
        bUseSize: true,
        bUseTmplType: false,
      });
      break;
    }
    case ConversionWayType.CppFromBP_NewFreeArrayData_CustomConvFunc: {
      result_map = genfunc_DefaultTmpl_CppFromBP_NewFreeArrayData({
        bUseSize: true,
        bUseTmplType: false,
      });
      break;
    }
    case ConversionWayType.CppFromBP_NeedCallCreateFreeRawData: {
      const conv_func_create = AGORA_MUSTACHE_DATA.CREATE_RAW_DATA;
      const conv_func_free = AGORA_MUSTACHE_DATA.FREE_RAW_DATA;
      const decl_func_create = AGORA_MUSTACHE_DATA.CREATE_RAW_DATA;
      const decl_func_free = AGORA_MUSTACHE_DATA.FREE_RAW_DATA;

      result_map = genfunc_DefaultTmpl_CallConvFunc(
        conv_func_create,
        conv_func_free,
        decl_func_create,
        decl_func_free
      );
      break;
    }
    case ConversionWayType.CppFromBP_NeedCallCustomConvFunc: {
      const conv_func_create = conv_cppfrombp.convFunc;
      const conv_func_free = conv_cppfrombp.convFuncAdditional01;
      const decl_func_create = data_decl_conv.convFunc;
      const decl_func_free = data_decl_conv.convFuncAdditional01;

      result_map = genfunc_DefaultTmpl_CallConvFunc(
        conv_func_create,
        conv_func_free,
        decl_func_create,
        decl_func_free
      );
      break;
    }
    case ConversionWayType.CppFromBP_CreateFreeOptData: {
      const conv_func_create = AGORA_MUSTACHE_DATA.CREATE_RAW_OPT_DATA;
      const conv_func_free = AGORA_MUSTACHE_DATA.FREE_RAW_OPT_DATA;
      const decl_func_create = AGORA_MUSTACHE_DATA.CREATE_RAW_OPT_DATA;
      const decl_func_free = AGORA_MUSTACHE_DATA.FREE_RAW_OPT_DATA;

      result_map = genfunc_DefaultTmpl_CallConvFunc(
        conv_func_create,
        conv_func_free,
        decl_func_create,
        decl_func_free
      );
      break;
    }

    case ConversionWayType.CppFromBP_NewFree_RawDataPtr1D: {
      const conv_func_new = AGORA_MUSTACHE_DATA.ConvFunc_New_RawDataPtr1D;
      const conv_func_free = AGORA_MUSTACHE_DATA.ConvFunc_Free_RawDataPtr1D;
      const decl_func_new = AGORA_MUSTACHE_DATA.ConvFunc_New_RawDataPtr1D;
      const decl_func_free = AGORA_MUSTACHE_DATA.ConvFunc_Free_RawDataPtr1D;

      result_map = genfunc_DefaultTmpl_CppFromBP_NewFreeData(
        { bUseSize: true, bUseTmplType: true },
        conv_func_new,
        conv_func_free,
        decl_func_new,
        decl_func_free
      );
      break;
    }

    case ConversionWayType.CppFromBP_NewFree_CustomRawDataPtr1D: {
      const conv_func_new = AGORA_MUSTACHE_DATA.ConvFunc_New_CustomRawDataPtr1D;
      const conv_func_free =
        AGORA_MUSTACHE_DATA.ConvFunc_Free_CustomRawDataPtr1D;
      const decl_func_new = AGORA_MUSTACHE_DATA.ConvFunc_New_CustomRawDataPtr1D;
      const decl_func_free =
        AGORA_MUSTACHE_DATA.ConvFunc_Free_CustomRawDataPtr1D;

      result_map = genfunc_DefaultTmpl_CppFromBP_NewFreeData(
        { bUseSize: true, bUseTmplType: true },
        conv_func_new,
        conv_func_free,
        decl_func_new,
        decl_func_free
      );
      break;
    }

    case ConversionWayType.CppFromBP_NewFree_CustomRawDataArray: {
      const conv_func_new = AGORA_MUSTACHE_DATA.ConvFunc_New_CustomRawDataArray;
      const conv_func_free =
        AGORA_MUSTACHE_DATA.ConvFunc_Free_CustomRawDataArray;
      const decl_func_new = AGORA_MUSTACHE_DATA.ConvFunc_New_CustomRawDataArray;
      const decl_func_free =
        AGORA_MUSTACHE_DATA.ConvFunc_Free_CustomRawDataArray;

      result_map = genfunc_DefaultTmpl_CppFromBP_NewFreeArrayData(
        { bUseSize: true, bUseTmplType: true },
        conv_func_new,
        conv_func_free,
        decl_func_new,
        decl_func_free
      );

      break;
    }

    case ConversionWayType.BPFromCpp_Func_SetBPDataArray_UCLASS: {
      const conv_func = AGORA_MUSTACHE_DATA.SET_BP_ARRAY_DATA_FOR_UCLASS;
      const decl_func = AGORA_MUSTACHE_DATA.SET_BP_ARRAY_DATA_FOR_UCLASS;
      result_map = genfunc_DefaultTmpl_SetArrayData(
        { bUseSize: true, bUseTmplType: true },
        conv_func,
        conv_func,
        decl_func
      );
      break;
    }

    case ConversionWayType.CppFromBP_NewFree_CustomRawDataArray_UCLASS: {
      const conv_func_new =
        AGORA_MUSTACHE_DATA.ConvFunc_New_CustomRawDataArrayUCLASS;
      const conv_func_free =
        AGORA_MUSTACHE_DATA.ConvFunc_Free_CustomRawDataArrayUCLASS;
      const decl_func_new =
        AGORA_MUSTACHE_DATA.ConvFunc_New_CustomRawDataArrayUCLASS;
      const decl_func_free =
        AGORA_MUSTACHE_DATA.ConvFunc_Free_CustomRawDataArrayUCLASS;

      result_map = genfunc_DefaultTmpl_CppFromBP_NewFreeArrayData(
        { bUseSize: true, bUseTmplType: true },
        conv_func_new,
        conv_func_free,
        decl_func_new,
        decl_func_free
      );
      break;
    }

    case ConversionWayType.CppFromBP_NewFree_RawDataArray: {
      const conv_func_new = AGORA_MUSTACHE_DATA.ConvFunc_New_RawDataArray;
      const conv_func_free = AGORA_MUSTACHE_DATA.ConvFunc_Free_RawDataArray;
      const decl_func_new = AGORA_MUSTACHE_DATA.ConvFunc_New_RawDataArray;
      const decl_func_free = AGORA_MUSTACHE_DATA.ConvFunc_Free_RawDataArray;

      result_map = genfunc_DefaultTmpl_CppFromBP_NewFreeArrayData(
        { bUseSize: true, bUseTmplType: true },
        conv_func_new,
        conv_func_free,
        decl_func_new,
        decl_func_free
      );
      break;
    }
  }

  const result = result_map[context_type] ?? '';
  return result;
}
