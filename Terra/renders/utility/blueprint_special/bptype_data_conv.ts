import { AGORA_MUSTACHE_DATA } from './bptype_mustache_data';

// [TBD] if need namespace or not ？

// TBD(WinterPu)
// Type conversion guide:
// Based on the type, you should know how to call and use it

// Difference between [TypeName], [DeclType] and [TypeSource]
// Ex.
// cpp type source: const char **
// [TypeName]: Ex. FString: used in the case: call class static method: FString::FromCStr()
//  or used in template type UABT::SetBPArrayData<FString, TArray<FString>(BPVar, CppArrayVar, CppArraySize);
// [DeclType]: Ex. TArray<FString>: used in the variable declaration: TArray<FString> MyArray; (usually in the function implementation)
// [TypeSource]: Ex. const TArray<FString> &: used in the function parameter: void MyFunc(const TArray<FString> &MyArray);

// Here: CppType to BPType
export type UEBPTypeConvData = {
  bpTypeName: string;
  bpDesignedDeclType: string | undefined;
  // skip the process, directly assigned the type source
  bpDesignedTypeSource: string | undefined;
  // whether the implementation is user provided. (not the native blueprint type)
  bpDesignedTypeDelegate: string | undefined;
  isCustomBPType: boolean;

  // [Step 1]: Basic Conversion: (Directly Type Conversion: Cpp <-> BP)
  // this mostly used in the USTRUCT conversion.
  // Ex. constructor(cpptype data){}
  // define the basic conversion way
  convFromCpp: CppBPConversionData;
  convToCpp: CppBPConversionData;

  // [Step 2]: Default Value
  // usually used in the USTRUCT member variable
  defaultValue: string | undefined;
  defaultBPValue: string | undefined;

  // [Step 3]: Parse Array
  // Black List: skip the parse process, not parsed as an array.
  parseArrayIsInBlackList: boolean;
  // White List: directly define the target array type.
  parseArrayDesignedType: string | undefined;

  // [Step 4]: Parse Pointer
  // Force Enable: the type would always be used as a pointer.
  // Ex. in TArray<T>, the UCLASS needs to be an pointer.
  parsePointerForceEnable: boolean;

  // [Step 5]: Return Type
  // directly define the target return type
  returnTypeDesignedType: string | undefined;
  // the default failed value, which could be used to return
  returnTypeFailedValue: string | undefined;

  // [Step 6]: Decl Type (Indirect Type Conversion: Cpp <-DeclType-> BP)
  // this mostly used in the UFUNCTION implementation
  // Ex. DeclType Raw_var = BPVar;
  // [Usage Reason comparing to Basic Conversion]:
  // 1. try to avoid (New / Free) operation
  // 2. When it has special usage way. Ex. need to call function stdstr.c_str();
  // In some cases, when you declare the type in the function body, you need to use other type as decl type.
  // Ex. const char* => FString, you could use std::string as decl type.
  // Here would define how the type is used in the function body.

  // Default: it would use Basic Conversion as default.
  // Ex
  // decl: CppType CppVar = BPVar;
  // usage: CppVar;
  // free: none
  declTypeSPRule: DeclTypeSPRule;

  // default:
  // [bp] -> TypeName or bpDesignedDeclType
  // [cpp] -> type name or cppDesignedDeclType
  cppDesignedDeclType: string | undefined;
};

export type CppBPConversionData = {
  convFuncType: ConversionWayType;
  convFunc: string;
  convFuncAdditional01: string; // Ex. free data conv function
  runtimedata?: any; // Ex. array size
};

export enum ConversionWayType {
  // no need conversion
  NoNeedConversion,

  // need call basic conversion method
  // Ex. A = ConvFunc(B);
  BasicConvFunc,

  DirectlyConv_StaticCast,

  DirectlyConv_ReinterpretCast,

  // [Part1]. BP = FuncFrom(Cpp);
  // need memory allocation
  // Ex. UABT::SetBPArrayData<CppType, BPType>(BPVar,CppArrayVar, CppArraySize);
  SetArrayData,
  SetArrayData_Size,
  SetArrayData_Size_TmplType,
  BPFromCpp_Func_SetBPDataArray,
  BPFromCpp_Func_SetBPDataArray_UCLASS,
  // BPFromCpp_Func_SetBPDataArray_USTRUCT,
  // BPVar = UTF8_TO_TCHAR(CppVar);
  BPFromCpp_FString,

  // [Part2]. Cpp = FuncTo(BP);
  // * need memory allocation
  // Ex. CppVar = UABT::New_ConvFunc(BPVar);
  // Ex. UABT::Free_ConvFunc(CppVar);
  CppFromBP_NewFreeData_CustomConvFunc,

  CppFromBP_NewFreeDataWithSize_CustomConvFunc,

  // need memory allocation
  // UABT::New_RawDataArray<CppType,BPType>(CppArrayVar,CppSize,BPVar);
  // UABT::Free_RawDataArray<CppType,BPType>(CppArrayVar,CppSize);
  CppFromBP_NewFreeArrayData_CustomConvFunc,
  // Directly Set Data
  // Ex. Convfunc_SetData(CppVar, BPVar, CppVarSize);
  // need call conversion function
  // Example: CreateRawData()
  // Ex. CppVar = BPVar.CreateRawData();
  // Ex. BPVar.FreeRawData(CppVar);
  CppFromBP_NeedCallCreateFreeRawData,
  // need call conversion function
  // Example: CreateRawData()
  // Ex. CppVar = BPVar.CreateRawData();
  // Ex. BPVar.FreeRawData(CppVar);
  CppFromBP_NeedCallCustomConvFunc,
  // ==== Custom Defined BP Var Only ====
  // * need memory allocation
  // Ex. CppVar = BPVar.CreateRawOptData();
  // Ex. BPVar.FreeRawOptData(CppVar);
  CppFromBP_CreateFreeOptData,

  CppFromBP_NewFree_RawDataPtr1D,
  CppFromBP_NewFree_CustomRawDataPtr1D,

  CppFromBP_NewFree_CustomRawDataArray_UCLASS,
  CppFromBP_NewFree_RawDataArray,
  CppFromBP_NewFree_CustomRawDataArray,
}

export enum DeclTypeSPRule {
  DefaultNoSP,
  // For String
  // CPPFromBP: Ex. const char* <= FString (decltype: std::string)
  // BPFromCPP: Ex. FString <= const char* (decltype: FString)
  SP_String,

  // For String
  // CPPFromBP: Ex.
  // GetDevice(FString & deviceId);
  // char Raw_DeviceId[512] = {0};
  // NativePtr->getDevice(Raw_DeviceId);
  // deviceId = UTF8_TO_TCHAR(Raw_DeviceId);
  // BPFromCPP: Ex.
  // getDevice(const char* deviceId);
  // FString BPDeviceId;
  // NativePtr->GetDevice(BPDeviceId);
  // UABT::SetCharArray(BPDeviceId, Raw_DeviceId,512);
  SP_String_Output_512,

  // For FVector
  // CPPFromBP: Ex. float const[3] <= FVector (decltype: float[3])
  // BPFromCPP: Ex. FVector <= float const[3] (decltype: FVector)
  SP_FVector,
}

export type DeclTypeFuncData = {
  funcDecl: (decl_var: string, param: string) => string;
  funcUsage: (decl_var: string) => string;
  funcFree: (bpTypeName?: string, decl_var?: string, param?: string) => string;
};

export type DeclTypeItemData = {
  CppFromBP: DeclTypeFuncData;
  BPFromCpp: DeclTypeFuncData;
};

export const map_decltype_special_rule = new Map<
  DeclTypeSPRule,
  DeclTypeItemData
>([
  [
    DeclTypeSPRule.SP_String,
    {
      // decl: std::string CppVar = TCHAR_TO_UTF8(*BPVar);
      // usage: CppVar.c_str();
      // free: none
      CppFromBP: {
        funcDecl: (decl_var, param) =>
          `std::string ${decl_var} = TCHAR_TO_UTF8(*${param});`,

        funcUsage: (decl_var) => `${decl_var}.c_str()`,

        funcFree: () => '',
      },
      // decl: FString BPVar = UTF8_TO_TCHAR(CppVar);
      // usage: BPVar;
      // free: none
      BPFromCpp: {
        funcDecl: (decl_var, param) =>
          `FString ${decl_var} = UTF8_TO_TCHAR(${param});`,

        funcUsage: (decl_var) => `${decl_var}`,

        funcFree: () => '',
      },
    },
  ],

  [
    DeclTypeSPRule.SP_String_Output_512,
    {
      // decl: char Raw_DeviceId[512] = {0};
      // usage: Raw_DeviceId;
      // free: none
      CppFromBP: {
        funcDecl: (decl_var, param) => `char ${decl_var}[512] = {0};`,

        funcUsage: (decl_var) => `${decl_var}`,

        funcFree: (byType, decl_var, param) =>
          `${param} = UTF8_TO_TCHAR(${decl_var});`,
      },
      BPFromCpp: {
        funcDecl: (decl_var, param) => `FString ${decl_var};`,

        funcUsage: (decl_var) => `${decl_var}`,

        funcFree: (byType, decl_var, param) =>
          `UABT::SetCharArray(${param}, ${decl_var}, 512);`,
      },
    },
  ],

  [
    DeclTypeSPRule.SP_FVector,
    {
      // decl: float[3] CppVar; UABT::SetFloatArray(BPVar, CppVar);
      // usage: CppVar;
      // free: none
      CppFromBP: {
        funcDecl: (decl_var, param) =>
          `float ${decl_var}[3]; UABT::SetFloatArray(${decl_var}, ${param});`,

        funcUsage: (decl_var) => `${decl_var}`,

        funcFree: () => '',
      },
      // decl: FVector BPVar = UABT::FromFloatArray(CppVar);
      // usage: BPVar;
      // free: none
      BPFromCpp: {
        funcDecl: (decl_var, param) =>
          `FVector ${decl_var} = UABT::FromFloatArray(${param});`,

        funcUsage: (decl_var) => `${decl_var}`,

        funcFree: () => '',
      },
    },
  ],
]);

export const map_one_category_basicconv_bpfromcpp = new Map<
  string,
  CppBPConversionData
>([
  [
    'Enum',
    {
      convFuncType: ConversionWayType.BasicConvFunc,
      convFunc: AGORA_MUSTACHE_DATA.UABTEnum_WrapWithUE,
      convFuncAdditional01: '',
    },
  ],
  [
    'TArray',
    {
      convFuncType: ConversionWayType.BPFromCpp_Func_SetBPDataArray,
      convFunc: '',
      convFuncAdditional01: '',
    },
  ],

  [
    'TArray_UCLASS',
    {
      convFuncType: ConversionWayType.BPFromCpp_Func_SetBPDataArray_UCLASS,
      convFunc: '',
      convFuncAdditional01: '',
    },
  ],

  [
    'TArray_USTRUCT',
    {
      convFuncType: ConversionWayType.BPFromCpp_Func_SetBPDataArray,
      convFunc: '',
      convFuncAdditional01: '',
    },
  ],
]);

export const map_one_category_basicconv_cppfrombp = new Map<
  string,
  CppBPConversionData
>([
  [
    'Enum',
    {
      convFuncType: ConversionWayType.BasicConvFunc,
      convFunc: AGORA_MUSTACHE_DATA.UABTEnum_ToRawValue,
      convFuncAdditional01: '',
    },
  ],

  [
    'Optional',
    {
      convFuncType: ConversionWayType.CppFromBP_CreateFreeOptData,
      convFunc: AGORA_MUSTACHE_DATA.CREATE_RAW_OPT_DATA,
      convFuncAdditional01: AGORA_MUSTACHE_DATA.FREE_RAW_OPT_DATA,
    },
  ],

  [
    'UCLASS_USTRUCT',
    {
      convFuncType: ConversionWayType.CppFromBP_NeedCallCustomConvFunc,
      convFunc: AGORA_MUSTACHE_DATA.CREATE_RAW_DATA,
      convFuncAdditional01: AGORA_MUSTACHE_DATA.FREE_RAW_DATA,
    },
  ],

  [
    'TArray',
    {
      convFuncType: ConversionWayType.CppFromBP_NewFree_RawDataArray,
      convFunc: '',
      convFuncAdditional01: '',
    },
  ],

  [
    'TArray_UCLASS',
    {
      convFuncType:
        ConversionWayType.CppFromBP_NewFree_CustomRawDataArray_UCLASS,
      convFunc: AGORA_MUSTACHE_DATA.ConvFunc_New_CustomRawDataArrayUCLASS,
      convFuncAdditional01:
        AGORA_MUSTACHE_DATA.ConvFunc_Free_CustomRawDataArrayUCLASS,
    },
  ],

  [
    'TArray_USTRUCT',
    {
      convFuncType: ConversionWayType.CppFromBP_NewFree_CustomRawDataArray,
      convFunc: '',
      convFuncAdditional01: '',
    },
  ],
]);

// =============== Default Template ===============
const defaultTmpl_BasicType_NoConv: UEBPTypeConvData = {
  bpTypeName: '',
  bpDesignedDeclType: undefined,
  bpDesignedTypeSource: undefined,
  bpDesignedTypeDelegate: undefined,
  isCustomBPType: false,
  convFromCpp: {
    convFuncType: ConversionWayType.NoNeedConversion,
    convFunc: '',
    convFuncAdditional01: '',
  },
  convToCpp: {
    convFuncType: ConversionWayType.NoNeedConversion,
    convFunc: '',
    convFuncAdditional01: '',
  },
  defaultValue: undefined,
  defaultBPValue: undefined,
  parseArrayIsInBlackList: false, // black list: no basic parse
  parseArrayDesignedType: undefined, // White list: basic parse
  parsePointerForceEnable: false, // UCLASS needs to be parsed as pointer
  returnTypeDesignedType: undefined,
  returnTypeFailedValue: undefined,
  declTypeSPRule: DeclTypeSPRule.DefaultNoSP,
  cppDesignedDeclType: undefined,
};

const defaultTmpl_FString_NonConst: UEBPTypeConvData = {
  // char* cppvar = UABT::New(bpvar);
  ...defaultTmpl_BasicType_NoConv,
  bpTypeName: 'FString',
  defaultValue: 'nullptr',
  defaultBPValue: 'TEXT("")',
  convFromCpp: {
    convFuncType: ConversionWayType.BPFromCpp_FString,
    convFunc: 'UTF8_TO_TCHAR',
    convFuncAdditional01: '',
  },
  convToCpp: {
    convFuncType: ConversionWayType.CppFromBP_NewFreeData_CustomConvFunc,
    convFunc: 'UABT::New_CharPtr1D',
    convFuncAdditional01: 'UABT::Free_CharPtr1D',
  },
  declTypeSPRule: DeclTypeSPRule.SP_String,
  parseArrayIsInBlackList: true,
};

const defaultTmpl_FString_NonConst_UnsignedChar: UEBPTypeConvData = {
  ...defaultTmpl_FString_NonConst,
  bpTypeName: 'FString',
  defaultValue: 'nullptr',
  defaultBPValue: 'TEXT("")',
  convFromCpp: {
    convFuncType: ConversionWayType.BPFromCpp_FString,
    convFunc: 'UTF8_TO_TCHAR',
    convFuncAdditional01: '',
  },
  convToCpp: {
    convFuncType: ConversionWayType.CppFromBP_NewFreeData_CustomConvFunc,
    convFunc: 'UABT::New_UnsignedCharPtr1D',
    convFuncAdditional01: 'UABT::Free_UnsignedCharPtr1D',
  },
  parseArrayIsInBlackList: true,
};

const defaultTmpl_FString_Const: UEBPTypeConvData = {
  ...defaultTmpl_BasicType_NoConv,
  bpTypeName: 'FString',
  defaultValue: 'nullptr',
  defaultBPValue: 'TEXT("")',
  convFromCpp: {
    convFuncType: ConversionWayType.BPFromCpp_FString,
    convFunc: 'UTF8_TO_TCHAR',
    convFuncAdditional01: '',
  },
  convToCpp: {
    convFuncType: ConversionWayType.CppFromBP_NewFreeData_CustomConvFunc,
    convFunc: 'UABT::New_CharPtr1D',
    convFuncAdditional01: 'UABT::Free_CharPtr1D',
  },
  declTypeSPRule: DeclTypeSPRule.SP_String,
  parseArrayIsInBlackList: true,
};

const defaultTmpl_FString_SetArray: UEBPTypeConvData = {
  ...defaultTmpl_BasicType_NoConv,
  bpTypeName: 'FString',
  convFromCpp: {
    convFuncType: ConversionWayType.BPFromCpp_FString,
    convFunc: 'UTF8_TO_TCHAR',
    convFuncAdditional01: '',
  },
  convToCpp: {
    convFuncType: ConversionWayType.SetArrayData_Size,
    convFunc: 'UABT::SetCharArray',
    convFuncAdditional01: '',
  },
  declTypeSPRule: DeclTypeSPRule.SP_String,
  parseArrayIsInBlackList: true,
};

const defaultTmpl_Int64_Pointer: UEBPTypeConvData = {
  ...defaultTmpl_BasicType_NoConv,
  bpTypeName: 'int64',
  convFromCpp: {
    convFuncType: ConversionWayType.DirectlyConv_ReinterpretCast,
    convFunc: '',
    convFuncAdditional01: '',
  },
  convToCpp: {
    convFuncType: ConversionWayType.DirectlyConv_ReinterpretCast,
    convFunc: '',
    convFuncAdditional01: '',
  },
};

const defaultTmpl_FUABT_OPT: UEBPTypeConvData = {
  ...defaultTmpl_BasicType_NoConv,
  isCustomBPType: true,
  convFromCpp: {
    convFuncType: ConversionWayType.NoNeedConversion,
    convFunc: '',
    convFuncAdditional01: '',
  },
  convToCpp: {
    convFuncType: ConversionWayType.CppFromBP_CreateFreeOptData,
    convFunc: AGORA_MUSTACHE_DATA.CREATE_RAW_OPT_DATA,
    convFuncAdditional01: AGORA_MUSTACHE_DATA.FREE_RAW_OPT_DATA,
  },
};

const defaultTmpl_TrackID: UEBPTypeConvData = {
  ...defaultTmpl_BasicType_NoConv,
  bpTypeName: 'int64',
  convFromCpp: {
    convFuncType: ConversionWayType.BasicConvFunc,
    convFunc: 'UABT::FromTrackID',
    convFuncAdditional01: '',
  },
  convToCpp: {
    convFuncType: ConversionWayType.BasicConvFunc,
    convFunc: 'UABT::ToTrackID',
    convFuncAdditional01: '',
  },
};

const defaultTmpl_FVector: UEBPTypeConvData = {
  ...defaultTmpl_BasicType_NoConv,
  bpTypeName: 'FVector',
  defaultValue: 'FVector(0.0, 0.0, 0.0)',
  parseArrayIsInBlackList: true,
  convFromCpp: {
    convFuncType: ConversionWayType.BasicConvFunc,
    convFunc: 'UABT::FromFloatArray',
    convFuncAdditional01: '',
  },
  convToCpp: {
    convFuncType: ConversionWayType.SetArrayData,
    convFunc: 'UABT::SetFloatArray',
    convFuncAdditional01: '',
  },
  declTypeSPRule: DeclTypeSPRule.SP_FVector,
};

// =============== Type 2 Type Conversion ===============
// also use type source as key
// but when the type is not on the map: we would use type.name to see if the base type is on the map
// Ex. uint8_t* => uint8_t => TArray<int>
export const map_cppreg_2_bptype_conv_data = new Map<RegExp, UEBPTypeConvData>([
  [
    // char const[n] => FString
    /(?:const\s+)?char\s*(?:const\s*)?\[\s*\d+\s*\]/g,
    {
      ...defaultTmpl_FString_SetArray,
      bpTypeName: 'FString',
    },
  ],

  [
    /(?:const\s+)?char\s*(?:const\s*)?\[\s*\d+\s*\]/g,
    {
      ...defaultTmpl_FString_SetArray,
      bpTypeName: 'FString',
    },
  ],
]);

// key is decided to use type source as key
// if we need to use type name as key, we could make a new map.
export const map_bptype_conv_data: { [type_source: string]: UEBPTypeConvData } =
  {
    // Basic Type
    'bool': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'bool',
      defaultValue: 'false',
    },
    'int': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int',
      defaultValue: '0',
    },
    'float': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'float',
      defaultValue: '0.0',
    },
    'double': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'FString',
      defaultValue: '0.0',
      convFromCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::FromDouble',
        convFuncAdditional01: '',
      },

      convToCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::ToDouble',
        convFuncAdditional01: '',
      },
    },

    // basic type
    'unsigned short': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int',
      defaultValue: '0',
    },
    'unsigned int': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int64',
      defaultValue: '0',
    },
    'long': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int64',
      defaultValue: '0',
    },

    'long long': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int64',
      defaultValue: '0',
    },

    // not builtin type
    'uint8_t': {
      // TBD(WinterPu) should be Byte, however Byte may not be supported in UE4.25
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int',
      defaultValue: '0',
    },
    'uint16_t': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int',
      defaultValue: '0',
    },
    'uint32_t': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int64',
      defaultValue: '0',
      convFromCpp: {
        convFuncType: ConversionWayType.NoNeedConversion,
        convFunc: '',
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::ToUInt32',
        convFuncAdditional01: '',
      },
    },
    'uint64_t': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'FString',
      // TBD(WinterPu)
      // in OnStreamMessage, uint64_t sentTs -> FString sentTs
      // because DECLARE_DYNAMIC_MULTICAST_DELEGATE_XXX would always gen FString to const FString &
      bpDesignedTypeDelegate: 'const FString &',
      bpDesignedTypeSource: 'const FString &',
      defaultValue: '0',
      convFromCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::FromUInt64ToFString',
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::ToUInt64FromFString',
        convFuncAdditional01: '',
      },
    },
    'int16_t': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int',
      defaultValue: '0',
    },
    'int32_t': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int',
      defaultValue: '0',
    },
    'int64_t': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int64',
      defaultValue: '0',
    },

    // FString Related
    'const char*': {
      ...defaultTmpl_FString_Const,
    },
    'char const*': {
      ...defaultTmpl_FString_Const,
    },
    'unsigned char const*': {
      ...defaultTmpl_FString_Const,
      convToCpp: {
        convFuncType: ConversionWayType.CppFromBP_NewFreeData_CustomConvFunc,
        convFunc: 'UABT::New_UnsignedCharPtr1D',
        convFuncAdditional01: 'UABT::Free_UnsignedCharPtr1D',
      },
    },
    'unsigned char*': {
      // TBD(WinterPu) check it
      ...defaultTmpl_FString_NonConst,
      bpTypeName: 'FString',
      convToCpp: {
        convFuncType: ConversionWayType.CppFromBP_NewFreeData_CustomConvFunc,
        convFunc: 'UABT::New_UnsignedCharPtr1D',
        convFuncAdditional01: 'UABT::Free_UnsignedCharPtr1D',
      },
    },
    'char*': {
      ...defaultTmpl_FString_NonConst,
      bpTypeName: 'FString',
    },

    'char const**': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'FString',
      bpDesignedTypeSource: 'const TArray<FString> &',
      bpDesignedDeclType: 'TArray<FString>',
      parsePointerForceEnable: true,
      convFromCpp: {
        convFuncType: ConversionWayType.SetArrayData_Size,
        convFunc: AGORA_MUSTACHE_DATA.SET_BP_FSTRING_TARRAY,
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType:
          ConversionWayType.CppFromBP_NewFreeArrayData_CustomConvFunc,
        convFunc: 'UABT::New_CharArray2D',
        convFuncAdditional01: 'UABT::Free_CharArray2D',
      },
      cppDesignedDeclType: 'char**',
    },

    'char**': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'FString',
      bpDesignedTypeSource: 'TArray<FString>',
      bpDesignedDeclType: 'TArray<FString>',
      parsePointerForceEnable: true,
      convFromCpp: {
        convFuncType: ConversionWayType.SetArrayData_Size,
        convFunc: AGORA_MUSTACHE_DATA.SET_BP_FSTRING_TARRAY,
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType:
          ConversionWayType.CppFromBP_NewFreeArrayData_CustomConvFunc,
        convFunc: 'UABT::New_CharArray2D',
        convFuncAdditional01: 'UABT::Free_CharArray2D',
      },
      cppDesignedDeclType: 'char**',
    },

    // FVector Related
    'float const[3]': {
      ...defaultTmpl_FVector,
    },

    'float[3]': {
      ...defaultTmpl_FVector,
    },

    // Array Related

    'float*': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'TArray<float>',
      convFromCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::FromFloatArray',
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType:
          ConversionWayType.CppFromBP_NewFreeArrayData_CustomConvFunc,
        convFunc: 'UABT::New_FloatArrayPtr',
        convFuncAdditional01: 'UABT::Free_FloatArrayPtr',
      },
    },

    'int const*': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int',
      bpDesignedDeclType: 'TArray<int>',
      bpDesignedTypeSource: 'const TArray<int> &',
      convFromCpp: {
        convFuncType: ConversionWayType.BPFromCpp_Func_SetBPDataArray,
        convFunc: '',
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType:
          ConversionWayType.CppFromBP_NewFreeArrayData_CustomConvFunc,
        convFunc: AGORA_MUSTACHE_DATA.NEW_RAW_ARRAY_DATA,
        convFuncAdditional01: AGORA_MUSTACHE_DATA.FREE_RAW_ARRAY_DATA,
      },
      cppDesignedDeclType: 'int*',
    },

    'uid_t*': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int64',
      bpDesignedTypeSource: 'TArray<int64>',
      convFromCpp: {
        convFuncType: ConversionWayType.BPFromCpp_Func_SetBPDataArray,
        convFunc: '',
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType:
          ConversionWayType.CppFromBP_NewFreeArrayData_CustomConvFunc,
        convFunc: 'UABT::New_UIDArrayPtr',
        convFuncAdditional01: 'UABT::Free_UIDArrayPtr',
      },
    },

    'agora::rtc::Music*': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'FUABT_Music',
      parseArrayIsInBlackList: true,
    },

    'agora::rtc::MusicChartInfo*': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'FUABT_MusicChartInfo',
      parseArrayIsInBlackList: true,
    },
    'agora::rtc::IScreenCaptureSourceList*': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'UAgoraBPuScreenCaptureSourceList',
      parseArrayIsInBlackList: true,
      parsePointerForceEnable: true,
    },

    // Pointer Related
    // because it could not be parsed as TArray<void>
    'void*': {
      // TBD(WinterPu) check it
      ...defaultTmpl_Int64_Pointer,
      bpTypeName: 'int64',
      defaultValue: '0',
      cppDesignedDeclType: 'void*',
    },
    'agora::view_t*': {
      // TBD(WinterPu) check it
      ...defaultTmpl_Int64_Pointer,
      bpTypeName: 'int64',
      defaultValue: '0',
      convFromCpp: {
        convFuncType: ConversionWayType.BPFromCpp_Func_SetBPDataArray,
        convFunc: '',
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType: ConversionWayType.CppFromBP_NewFree_CustomRawDataPtr1D,
        convFunc: '',
        convFuncAdditional01: '',
      },
    },

    // Agora Related
    'agora::rtc::uid_t': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int64',
      convFromCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::FromUID',
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::ToUID',
        convFuncAdditional01: '',
      },
    },
    'agora::user_id_t': {
      ...defaultTmpl_FString_Const,
      convToCpp: {
        convFuncType: ConversionWayType.CppFromBP_NewFreeData_CustomConvFunc,
        convFunc: 'UABT::New_CharPtr1D',
        convFuncAdditional01: 'UABT::Free_CharPtr1D',
      },
    },
    'agora::view_t': {
      // TBD(WinterPu) store pointer address
      // TBD(WinterPu) combine it to tmpl
      ...defaultTmpl_Int64_Pointer,
      bpTypeName: 'int64',
      convFromCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::FromView',
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::ToView',
        convFuncAdditional01: '',
      },
    },
    'media::base::view_t': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int64',
      convFromCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::FromView',
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::ToView',
        convFuncAdditional01: '',
      },
    },
    'base::user_id_t': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'FString',
    },
    'rtc::uid_t': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int64',
    },
    'rtc::track_id_t': {
      ...defaultTmpl_TrackID,
      bpTypeName: 'int64',
      convFromCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::FromVTID',
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::ToVTID',
        convFuncAdditional01: '',
      },
    },
    'agora::rtc::track_id_t': {
      ...defaultTmpl_TrackID,
      bpTypeName: 'int64',
      // TBD(WinterPu) combine it to tmpl
      convFromCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::FromVTID',
        convFuncAdditional01: '',
      },
      convToCpp: {
        convFuncType: ConversionWayType.BasicConvFunc,
        convFunc: 'UABT::ToVTID',
        convFuncAdditional01: '',
      },
    },
    'agora::rtc::video_track_id_t': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int64',
    },
    'agora::util::AString&': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'FString',
    },

    'size_t': {
      ...defaultTmpl_BasicType_NoConv,
      bpTypeName: 'int64',
      defaultValue: '0',
    },

    // Custom Defined Type
    'Optional<bool>': {
      ...defaultTmpl_FUABT_OPT,
      bpTypeName: 'FUABT_Opt_bool',
    },
    'Optional<agora::rtc::VIDEO_STREAM_TYPE>': {
      ...defaultTmpl_FUABT_OPT,
      bpTypeName: 'FUABT_Opt_VIDEO_STREAM_TYPE',
    },
    'Optional<double>': {
      ...defaultTmpl_FUABT_OPT,
      bpTypeName: 'FUABT_Opt_double',
    },
    'Optional<int>': {
      ...defaultTmpl_FUABT_OPT,
      bpTypeName: 'FUABT_Opt_int',
    },
    'Optional<agora::rtc::CAMERA_DIRECTION>': {
      ...defaultTmpl_FUABT_OPT,
      bpTypeName: 'FUABT_Opt_CAMERA_DIRECTION',
    },
    'Optional<agora::rtc::CAMERA_FOCAL_LENGTH_TYPE>': {
      ...defaultTmpl_FUABT_OPT,
      bpTypeName: 'FUABT_Opt_CAMERA_FOCAL_LENGTH_TYPE',
    },
    'Optional<const char *>': {
      ...defaultTmpl_FUABT_OPT,
      bpTypeName: 'FUABT_Opt_ConstCharPtr',
    },
    'Optional<agora::rtc::CLIENT_ROLE_TYPE>': {
      ...defaultTmpl_FUABT_OPT,
      bpTypeName: 'FUABT_Opt_CLIENT_ROLE_TYPE',
    },
    'Optional<agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE>': {
      ...defaultTmpl_FUABT_OPT,
      bpTypeName: 'FUABT_Opt_AUDIENCE_LATENCY_LEVEL_TYPE',
    },
    'Optional<agora::CHANNEL_PROFILE_TYPE>': {
      ...defaultTmpl_FUABT_OPT,
      bpTypeName: 'FUABT_Opt_CHANNEL_PROFILE_TYPE',
    },
    'Optional<agora::rtc::video_track_id_t>': {
      ...defaultTmpl_FUABT_OPT,
      bpTypeName: 'FUABT_Opt_video_track_id_t',
    },
    'Optional<agora::rtc::THREAD_PRIORITY_TYPE>': {
      ...defaultTmpl_FUABT_OPT,
      bpTypeName: 'FUABT_Opt_THREAD_PRIORITY_TYPE',
    },
  };

// =============== Specific To One Variable Special Rule ===============
// key: variable full name

// be special to one case
export const map_struct_member_variable_default_value: {
  [key: string]: string;
} = {
  /*
   * (Recommended) 0: Standard bitrate mode.
   *
   * In this mode, the video bitrate is twice the base bitrate.
   */
  // const int STANDARD_BITRATE = 0;
  'agora::rtc::ScreenCaptureParameters.bitrate': '0',
  'agora::rtc::VideoEncoderConfiguration.bitrate': '0',
  /**
   * -1: (For future use) The default minimum bitrate.
   */
  // const int DEFAULT_MIN_BITRATE = -1;
  'agora::rtc::VideoEncoderConfiguration.minBitrate': '-1',

  'agora::rtc::ScreenCaptureParameters.contentHint':
    'EUABT_VIDEO_CONTENT_HINT::CONTENT_HINT_MOTION',

  // [because of macro_scope] contentHint is in not available on Windows
  // therefore it shows: EUABT_VIDEO_CONTENT_HINT contentHint = UABTEnum::WrapWithUE(undefined);
  'agora::rtc::ScreenVideoParameters.contentHint':
    'EUABT_VIDEO_CONTENT_HINT::CONTENT_HINT_NONE',

  // for macro scope problem:
  'agora::rtc::ScreenCaptureSourceInfo.type':
    'EUABT_ScreenCaptureSourceType::ScreenCaptureSourceType_Unknown',
};

// In Struct, the corresponding size count variable to the target member variable
export const map_struct_member_variable_size_count: { [key: string]: string } =
  {
    'agora::rtc::FocalLengthInfagora::rtc::DownlinkNetworkInfo::PeerDownlinkInfo.peer_downlink_info':
      'total_received_video_count',

    'agora::rtc::ChannelMediaRelayConfiguration.destInfos': 'destCount',
  };

// In Method, the corresponding size count variable to the target member variable
export const map_method_param_size_count: { [key: string]: string } = {};

// // Ex.
// export const map_empty_name_enum: { [key: string]: string } = {
//   /*
//     class IAudioFrameObserverBase {
//     public:
//     enum { MAX_HANDLE_TIME_CNT = 10 };
//   };
//   */
//   'agora::media::IAudioFrameObserverBase': 'MAX_HANDLE_TIME_CNT',

//   /*
//   #ifndef OPTIONAL_ENUM_SIZE_T
//   #if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
//   #define OPTIONAL_ENUM_SIZE_T enum : size_t
//   #else
//   #define OPTIONAL_ENUM_SIZE_T enum
//   #endif
//   #endif

//   struct VideoFormat {
//     OPTIONAL_ENUM_SIZE_T{
//         kMaxWidthInPixels = 3840,
//         kMaxHeightInPixels = 2160,
//         kMaxFps = 60,
//     };
//   };
//   */
//   'agora::rtc::VideoFormat': 'VideoFormat_OPTIONAL_ENUM_SIZE_T',

//   /*
//   struct AudioPcmFrame {
//     OPTIONAL_ENUM_SIZE_T{
//         kMaxDataSizeSamples = 3840,
//         kMaxDataSizeBytes = kMaxDataSizeSamples * sizeof(int16_t),
//     };
//   };
//   */
//   'agora::rtc::AudioPcmFrame': 'AudioPcmFrame_OPTIONAL_ENUM_SIZE_T',
// };

export const map_class_struct_without_default_constructor: {
  [key: string]: string;
} = {
  'agora::rtc::MixedAudioStream':
    'agora::rtc::MixedAudioStream AgoraData(agora::rtc::AUDIO_SOURCE_TYPE::AUDIO_SOURCE_UNKNOWN);',
};

export const map_callback_no_void_return_val: { [key: string]: string } = {};

// [return_type_source] -> [BP default value]
export const map_return_bptype_default_value: Record<string, string> = {
  'int': 'AGORA_UE_ERR_CODE(ERROR_NULLPTR)',
  'char const*': 'nullptr',
  'bool': 'false',
  'agora_refptr': 'nullptr',
  'agora::rtc::video_track_id_t': '0',
  'float': '0.0f',
  'agora::rtc::IScreenCaptureSourceList*': 'nullptr',
  'agora::rtc::CONNECTION_STATE_TYPE':
    'UABTEnum::WrapWithUE(agora::rtc::CONNECTION_STATE_TYPE::CONNECTION_STATE_FAILED)',
  'int64_t': '0',
  'uint64_t': 'TEXT("0")',
  'agora_refptr<agora::rtc::IMediaPlayer>': 'nullptr',
  'agora_refptr<agora::rtc::IMediaRecorder>': 'nullptr',
  'void': '',

  // // TBD(WinterPu) They are in AgoraBPuAgoraMediaBase.cpp
  // 'int64': '0',
  // 'EUABT_VIDEO_FRAME_PROCESS_MODE':
  //   'EUABT_VIDEO_FRAME_PROCESS_MODE::PROCESS_MODE_READ_WRITE',
  // 'EUABT_VIDEO_PIXEL_FORMAT': 'EUABT_VIDEO_PIXEL_FORMAT::VIDEO_PIXEL_DEFAULT',
};

export const map_return_bptype_fix: { [key: string]: string } = {};

export const map_return_context_default_value: { [key: string]: string } = {
  int64: '0',
};
