import { SimpleType } from '@agoraio-extensions/cxx-parser';
import {
  CXXTYPE,
  CXXTerraNode,
  MemberFunction,
} from '@agoraio-extensions/cxx-parser/src/cxx_terra_node';

import { map_failure_return_val } from '../filter_helper';
import * as Logger from '../logger';
import * as Tools from '../tools';

import { map_callback_no_void_return_val } from './bptype_data_conv';
import { AGORA_MUSTACHE_DATA } from './bptype_mustache_data';

export enum BPNodeCategoryType {
  File,
  UClass,
  UStruct,
  UEnum,
  Method,
  CallbackDelegate,
  ParamType,
  ReturnType,
}

export function genBPFileName(file_name: string): string {
  let res_name = file_name;
  if (res_name.startsWith('I')) {
    res_name = res_name.slice(1); // 去掉开头的 I
  }
  return AGORA_MUSTACHE_DATA.BPFileName_Prefix + res_name;
}

export function getBPTypeRegisteredKey(node: CXXTerraNode): string {
  // notice, it would pass: SimpleType to [getBPTypeRegisteredKey]:
  let key_registeredtype = node.name ?? '';

  if (node.__TYPE === CXXTYPE.SimpleType) {
    if (isCustomDefinedBPType_Optional(node.asSimpleType())) {
      key_registeredtype = node.source;
    }
    key_registeredtype = Tools.convertTypeNameToNodeName(key_registeredtype);
  }

  // TBD(WinterPu)
  // Currently skip it: because anonymous enum has no idea about cpp type
  // Ex.
  //   class IAudioFrameObserverBase {
  //   public:
  //   enum { MAX_HANDLE_TIME_CNT = 10 };
  //   };
  //   */
  //   'agora::media::IAudioFrameObserverBase': 'MAX_HANDLE_TIME_CNT',
  //  [Error]: agora::media::IAudioFrameObserverBase::?? Result;

  //   if (node.__TYPE === CXXTYPE.Enumz && key_registeredtype === '') {
  //     key_registeredtype = map_empty_name_enum[node.parent_full_scope_name ?? ''];
  //   }

  return key_registeredtype;
}

export function genBPNodeName(
  key_registeredtype: string,
  type: BPNodeCategoryType
): string {
  let result = '';
  if (type === BPNodeCategoryType.UClass) {
    // For UClass
    let clazz_name = key_registeredtype;
    // legency issue
    // Because the design previously removed the leading 'I'.
    // ex. IRtcEngine => UAgoraBPuRtcEngine
    // TBD(WinterPu)
    // Ex. like Iterator, Interface, etc. Which the leading 'I' is not removed.
    if (clazz_name.startsWith('I')) {
      clazz_name = clazz_name.slice(1); // 去掉开头的 I
    }
    result = AGORA_MUSTACHE_DATA.UEBP_PREFIX_CLASS + clazz_name;
  } else if (type === BPNodeCategoryType.UStruct) {
    // For UStruct
    let struct_name = key_registeredtype;
    result = AGORA_MUSTACHE_DATA.UEBP_PREFIX_STRUCT + struct_name;
  } else if (type === BPNodeCategoryType.UEnum) {
    // For UEnum
    let enum_name = key_registeredtype;
    result = AGORA_MUSTACHE_DATA.UEBP_PREFIX_ENUM + enum_name;
  }
  return result;
}

export type BPMethodName = {
  // Ex.
  // DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAgoraMediaEngineEvent, FString, Name);
  // delegateMacroName: DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam
  // delegateTypeName: FOnAgoraMediaEngineEvent
  // delegateVarName: OnAgoraMediaEngineEvent
  // delegateIsNoParam: false
  methodName: string;
  delegateMacroName: string;
  delegateTypeName: string;
  delegateVarName: string;
  delegateIsNoParam: boolean;
  delegateNoVoidReturnVal: boolean;
  delegateNoVoidReturnImpl: string;
};

const bp_multicast_number_prefix: string[] = [
  'One',
  'Two',
  'Three',
  'Four',
  'Five',
  'Six',
  'Seven',
  'Eight',
  'Nine',
];

export function genBPMethodName(
  node_method: MemberFunction,
  isCallback: boolean = false
): BPMethodName {
  // gen bp method name
  const _genBPMethodName = function (method_name: string): string {
    if (!method_name) return ''; // handle empty string
    return method_name.charAt(0).toUpperCase() + method_name.slice(1);
  };
  const method_name = _genBPMethodName(node_method.name);

  if (!isCallback) {
    return {
      methodName: method_name,
      delegateMacroName: '',
      delegateTypeName: '',
      delegateVarName: '',
      delegateIsNoParam: false,
      delegateNoVoidReturnVal: false,
      delegateNoVoidReturnImpl: '',
    };
  }

  // if the method is a callback method
  let len_params = node_method.parameters.length;
  let val_macro_name = '';
  if (len_params > 9) {
    Logger.PrintError(`Error: Invalid number of parameters: ${len_params}`);
    val_macro_name = 'NoDelegate';
  } else if (len_params == 0) {
    val_macro_name = 'DECLARE_DYNAMIC_MULTICAST_DELEGATE';
  } else if (len_params == 1) {
    val_macro_name = 'DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam';
  } else {
    val_macro_name = `DECLARE_DYNAMIC_MULTICAST_DELEGATE_${
      bp_multicast_number_prefix[len_params - 1]
    }Params`;
  }

  let bIsNoVoid = node_method.return_type.name !== 'void';
  let bpContextNoVoidImpl = '';

  if (map_callback_no_void_return_val[node_method.return_type.source]) {
    bIsNoVoid = true;
    bpContextNoVoidImpl = `${
      map_callback_no_void_return_val[node_method.return_type.source]
    }`;
  } else {
    if (bIsNoVoid) {
      // TBD(WinterPu)
      // tmp use old map [map_failure_return_val]
      // need to be replaced.
      const val_return_type =
        map_failure_return_val[node_method.return_type.name];
      if (val_return_type) {
        bpContextNoVoidImpl = `return ${val_return_type};`;
      }
    }
  }

  return {
    methodName: method_name,
    delegateMacroName: val_macro_name,
    delegateTypeName: `F${method_name}`,
    delegateVarName: `${method_name}`,
    delegateIsNoParam: len_params === 0,
    delegateNoVoidReturnVal: bIsNoVoid,
    delegateNoVoidReturnImpl: bpContextNoVoidImpl,
  };
}

export function isCustomDefinedBPType_Optional(type: SimpleType): boolean {
  return type.name === 'Optional';
}
