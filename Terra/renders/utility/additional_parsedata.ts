// Define custom user data for code generation

import { UEBPType } from './blueprint_special/bptype_helper';

export class CXXFileUserData {
  fileName: string = '';
  bpFileName: string = '';
  bpIncludeFiles: string[] = [];
}

export class UECommonUserData {
  commentCppStyle: string = '';
  macro_scope_start: string = '';
  macro_scope_end: string = '';

  // bp
  bpNodeName: string = '';
  bpHasRegistered: boolean = false; // if the node is class, struct, enum, it would be registered first.
}

export class TerraNodeUserData extends UECommonUserData {
  isStruct: boolean = false;
  isEnumz: boolean = false;
  isClazz: boolean = false;
  isCallback: boolean = false;
  prefix_name: string = '';

  // bp
}

export class SimpleTypeUserData {
  bpType: UEBPType = new UEBPType();
}

export class ClazzUserData extends UECommonUserData {
  bpContextInst: string = '';
  bpContextInitDecl: string = '';
  bpContextInitImpl: string = '';
}

export class ClazzMethodUserData extends UECommonUserData {
  isExcluded: boolean = false;
  failureReturnVal: string = '';
  hasReturnVal: boolean = false;
  hasParameters: boolean = false;
  isRegisterMethod: boolean = false;
  isSupport: boolean = false;
  bindingEventExtension: string[] = [];
  bindingExtension: string[] = [];

  isFirst: boolean = false;
  isLast: boolean = false;
  callerInstanceName: string = '';

  suffix_attribute: string = '';

  // bp
  bpContextReplacedDecl: boolean = false;
  bpContextReplacedDecl_IncludingComments: boolean = false;
  bpContextReplcedMethodDeclaration: string = '';
  bpContextReplacedImpl: boolean = false;
  bpContextReplcedMethodImplementation: string = '';

  bpReturnType: string = '';
  bpCallbackDelegateMacroName: string = '';
  bpCallbackDelegateTypeName: string = '';
  bpCallbackDelegateVarName: string = '';
  bpCallbackIsNoParam: boolean = false;

  bpCallbackIsNoVoidReturnVal: boolean = false;
  bpContextCallbackNoVoidReturnImpl: string = '';

  bpContextReturnValBegin: string = '';
  bpContextReturnValSetVal: string = '';
  bpContextReturnValEnd: string = '';

  bpContextParamsDecl_CppFromBP: string = '';
  bpContextParamsUsage_CppFromBP: string = '';
  bpContextParamsFree_CppFromBP: string = '';
  bpContextParamsDecl_BPFromCpp: string = '';
  bpContextParamsUsage_BPFromCpp: string = '';
  bpContextParamsFree_BPFromCpp: string = '';
  bpNativePtr: string = '';
}

export class EnumConstantsUserData extends UECommonUserData {
  isFirst: boolean = false;
  isLast: boolean = false;
}

export class StructUserData extends UECommonUserData {
  bpContextConstructor: string = '';
  bpContextCreateRawData: string = '';
  bpContextFreeRawData: string = '';
}

export class StructMemberVariableUserData extends UECommonUserData {
  // bp
  bpFormatDefaultVal: string = '';
}

export class ParameterUserData extends UECommonUserData {
  isFirst: boolean = false;
  isLast: boolean = false;
  defaultValue: string = '';
  defaultValueComment: string = ''; // used in impl: ex. void Func(int a /*1*/)
  // bp
  bpParameterType: string = '';
  bpDelegateType: string = '';
}

//////// Define Custom UserData
