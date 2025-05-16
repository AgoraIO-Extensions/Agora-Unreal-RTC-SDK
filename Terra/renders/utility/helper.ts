import * as path from 'path';

import {
  CXXFile,
  CXXTYPE,
  CXXTerraNode,
  ConstructorInitializer,
  SimpleType,
  Variable,
} from '@agoraio-extensions/cxx-parser';

import {
  ParseResult,
  RenderResult,
  TerraContext,
} from '@agoraio-extensions/terra-core';

import {
  MustacheRenderConfiguration,
  renderWithConfiguration,
} from '@agoraio-extensions/terra_shared_configs';

import * as CustomUserData from './additional_parsedata';

import * as BPHelper from './blueprint_special/bp_helper';

import * as CppHelper from './cpp_helper';
import * as FilterHelper from './filter_helper';
import * as Logger from './logger';
import * as Tools from './tools';

export function preProcessNode(cxxfiles: CXXFile[]) {
  // bp preprocess: register data
  BPHelper.registerBPTypes(cxxfiles);
}

export type FilterTerraNodeFunction = (cxxfile: CXXFile) => CXXTerraNode[];

export type ExcludeApiFunction = (method_name: string) => boolean;

// main function
export function genGeneralTerraData(
  terraContext: TerraContext,
  args: any,
  parseResult: ParseResult,
  func_filter_terrnode?: FilterTerraNodeFunction,
  func_exclude_api?: ExcludeApiFunction
): any {
  let cxxfiles = parseResult.nodes as CXXFile[];

  // [Step 0: Preparation]
  preProcessNode(cxxfiles);

  // [-- Define Functions]
  const genBaseUECommonUserData = function (
    node: CXXTerraNode
  ): CustomUserData.UECommonUserData {
    let [typeCategoryName, valBPNodeName] = BPHelper.getBPName(node);

    const userdata: CustomUserData.UECommonUserData = {
      commentCppStyle: CppHelper.formatAsCppComment(node.comment),
      macro_scope_start: CppHelper.createCompilationDirectivesContent(node),
      macro_scope_end: CppHelper.createCompilationDirectivesContent(
        node,
        false
      ),
      // bp
      bpNodeName: valBPNodeName,
      bpHasRegistered: typeCategoryName !== CXXTYPE.Unknown,
    };

    return userdata;
  };

  // [Step 1: Parse the nodes]
  let view = cxxfiles.map((cxxfile: CXXFile) => {
    // Base Node - File
    const valFileName = CppHelper.getFileName(cxxfile);
    const includeFiles = BPHelper.getIncludeFilesForBP(cxxfile);
    const cxxUserData: CustomUserData.CXXFileUserData = {
      fileName: valFileName,
      bpFileName: BPHelper.getBPFileName(valFileName),
      bpIncludeFiles: includeFiles,
    };
    cxxfile.user_data = cxxUserData;

    // Apply Filter if defined
    let nodes = cxxfile.nodes;
    if (func_filter_terrnode) {
      nodes = func_filter_terrnode(cxxfile);
    }

    nodes = nodes.filter((node) => {
      return !BPHelper.filterEmptyNameNode(node);
    });

    cxxfile.nodes = nodes.map((node: CXXTerraNode) => {
      // Base Node - TerraNode
      const basedata = genBaseUECommonUserData(node);
      const terraNodeUserData: CustomUserData.TerraNodeUserData = {
        ...basedata,
        isStruct: node.__TYPE === CXXTYPE.Struct,
        isEnumz: node.__TYPE === CXXTYPE.Enumz,
        isClazz: node.__TYPE === CXXTYPE.Clazz,
        isCallback: CppHelper.isCallbackClazz(node),
        prefix_name: node.name.replace(new RegExp('^I(.*)'), '$1'),
      };
      node.user_data = { ...node.user_data, ...terraNodeUserData };

      // Node - Clazz
      if (node.__TYPE == CXXTYPE.Clazz) {
        let bIsCallbackMethod = CppHelper.isCallbackClazz(node);

        let context_clazz = BPHelper.genContext_BPClass(node.asClazz());

        const basedata_clazz = genBaseUECommonUserData(node);
        const clazzUserData: CustomUserData.ClazzUserData = {
          ...node.user_data,
          ...basedata_clazz,
          bpContextInst: context_clazz?.Inst ?? '',
          bpContextInitDecl: context_clazz?.InitDecl ?? '',
          bpContextInitImpl: context_clazz?.InitImpl ?? '',
        };
        node.user_data = clazzUserData;

        // Node - Clazz Method
        node.asClazz().methods.map((method, index) => {
          const contextBPMethod = BPHelper.genContext_BPMethod(
            method,
            '      '
          );
          const bpMethodNameFullData = BPHelper.getBPMethodNameFullData(
            method,
            bIsCallbackMethod
          );
          const basedata_clazzmethod = genBaseUECommonUserData(method);
          const replaced_context =
            BPHelper.genContext_BPMethodReplacedDecl(method);
          const clazzMethodUserData: CustomUserData.ClazzMethodUserData = {
            ...basedata_clazzmethod,
            isExcluded: func_exclude_api
              ? func_exclude_api(method.name)
              : false,
            failureReturnVal: FilterHelper.UESDK_GetFailureReturnVal(
              method.return_type.source
            ),
            hasReturnVal: method.return_type.source.toLowerCase() !== 'void',

            suffix_attribute: CppHelper.genSuffixAttribute(method.attributes),
            isFirst: index === 0,
            isLast: index === node.asClazz().methods.length - 1,
            callerInstanceName:
              method.parent_name === 'IRtcEngineEx'
                ? '((IRtcEngineEx*)RtcEngine)'
                : 'RtcEngine',

            // bp

            bpContextReplacedDecl: replaced_context.doReplceDecl,
            bpContextReplacedDecl_IncludingComments:
              replaced_context.declOp_IncludingComments,
            bpContextReplcedMethodDeclaration: replaced_context.decl,
            bpContextReplacedImpl: replaced_context.doReplceImpl,
            bpContextReplcedMethodImplementation: replaced_context.impl,

            bpReturnType: BPHelper.genBPReturnType(method.return_type),

            bpCallbackDelegateMacroName: bpMethodNameFullData.delegateMacroName,
            bpCallbackDelegateTypeName: bpMethodNameFullData.delegateTypeName,
            bpCallbackDelegateVarName: bpMethodNameFullData.delegateVarName,
            bpCallbackIsNoParam: bpMethodNameFullData.delegateIsNoParam,
            bpCallbackIsNoVoidReturnVal:
              bpMethodNameFullData.delegateNoVoidReturnVal,
            bpContextCallbackNoVoidReturnImpl:
              bpMethodNameFullData.delegateNoVoidReturnImpl,

            bpContextParamsDecl_BPFromCpp:
              contextBPMethod.contextParam_BPFromCpp.contextDecl,
            bpContextParamsUsage_BPFromCpp:
              contextBPMethod.contextParam_BPFromCpp.contextUsage,
            bpContextParamsFree_BPFromCpp:
              contextBPMethod.contextParam_BPFromCpp.contextFree,

            bpContextParamsDecl_CppFromBP:
              contextBPMethod.contextParam_CppFromBP.contextDecl,
            bpContextParamsUsage_CppFromBP:
              contextBPMethod.contextParam_CppFromBP.contextUsage,
            bpContextParamsFree_CppFromBP:
              contextBPMethod.contextParam_CppFromBP.contextFree,

            bpContextReturnValBegin: contextBPMethod.contextReturnValBegin,
            bpContextReturnValSetVal: contextBPMethod.contextReturnValSetVal,
            bpContextReturnValEnd: contextBPMethod.contextReturnValEnd,

            bpNativePtr: BPHelper.genContext_BPMethod_NativePtr(method),
            ...method.user_data,
          };
          method.user_data = clazzMethodUserData;

          // Handle Variadic Params '....'
          if (method.is_variadic) {
            let param_variadic = new Variable();
            param_variadic.name = '...';
            param_variadic.source = '...';
            param_variadic.type = new SimpleType();
            param_variadic.type.clang_qualtype = '';
            method.parameters.push(param_variadic);
          }

          // Node - Clazz Method Parameter
          method.parameters.map((parameter, index) => {
            let valDefaultVal = CppHelper.prettyDefaultValue(
              parseResult,
              parameter.type,
              parameter.default_value
            );
            let commentDefaultValue =
              valDefaultVal !== '' ? ' /* ' + valDefaultVal + ' */ ' : '';
            valDefaultVal = valDefaultVal !== '' ? ' = ' + valDefaultVal : '';

            const bpType = BPHelper.genBPParameterType(parameter);
            const basedata_parameter = genBaseUECommonUserData(parameter);
            const parameterUserData: CustomUserData.ParameterUserData = {
              ...basedata_parameter,
              commentCppStyle: CppHelper.formatAsCppComment(parameter.comment),
              isFirst: index === 0,
              isLast: index === method.parameters.length - 1,
              defaultValue: valDefaultVal,
              defaultValueComment: commentDefaultValue,

              // bp
              bpParameterType: bpType.source,
              bpDelegateType: bpType.delegateType,
              ...parameter.user_data,
            };
            parameter.user_data = parameterUserData;
          });
        });
      } else if (node.__TYPE == CXXTYPE.Enumz) {
        // Node - Enumz
        node.asEnumz().enum_constants.map((enum_constant, index) => {
          const basedata_enumconstant = genBaseUECommonUserData(enum_constant);
          const enumConstantsUserData: CustomUserData.EnumConstantsUserData = {
            ...basedata_enumconstant,
            isFirst: index === 0,
            isLast: index === node.asEnumz().enum_constants.length - 1,
          };
          enum_constant.user_data = {
            ...enum_constant.user_data,
            ...enumConstantsUserData,
          };
        });
      } else if (node.__TYPE == CXXTYPE.Struct) {
        // Node - Struct
        const dictInitializer = BPHelper.prepareBPStructInitializerDict(
          node.asStruct()
        );
        const contextStruct = BPHelper.genContext_BPStruct(node.asStruct(), '		');
        const basedata_struct = genBaseUECommonUserData(node);
        const structUserData: CustomUserData.StructUserData = {
          ...basedata_struct,
          bpContextConstructor: contextStruct.contextConstructor,
          bpContextCreateRawData: contextStruct.contextCreateRawData,
          bpContextFreeRawData: contextStruct.contextFreeRawData,
        };
        node.user_data = {
          ...node.user_data,
          ...structUserData,
        };

        // Node - Struct Member Variable
        node.asStruct().member_variables.map((member_variable, index) => {
          const bpType = BPHelper.getBPType(member_variable.type);
          const simpleTypeUserData: CustomUserData.SimpleTypeUserData = {
            bpType: bpType,
          };
          member_variable.type.user_data = simpleTypeUserData;

          const formatDefaultVal = BPHelper.getBPStructData_DefaultVal(
            dictInitializer,
            member_variable,
            bpType
          );

          const basedata_structmembervariable =
            genBaseUECommonUserData(member_variable);
          const structMemberVariableUserData: CustomUserData.StructMemberVariableUserData =
            {
              ...basedata_structmembervariable,
              bpFormatDefaultVal: formatDefaultVal,
            };
          member_variable.user_data = {
            ...member_variable.user_data,
            ...structMemberVariableUserData,
          };
        });
      }

      return node;
    });
    return cxxfile;
  });

  // [Step 2: Filter nodes]
  //remove neither Clazz, Enumz nor Struct exist in the file
  view = view.filter((cxxfile) => {
    return (
      cxxfile.nodes.filter((node) => {
        return (
          node.__TYPE === CXXTYPE.Clazz ||
          node.__TYPE === CXXTYPE.Enumz ||
          node.__TYPE === CXXTYPE.Struct
        );
      }).length > 0
    );
  });

  return view;
}

export function mergeAllNodesToOneCXXFile(view: CXXFile[]): CXXFile {
  const allNodesFile = new CXXFile();

  view.forEach((cxxfile: CXXFile) => {
    allNodesFile.nodes = [...allNodesFile.nodes, ...cxxfile.nodes];
  });

  return allNodesFile;
}
