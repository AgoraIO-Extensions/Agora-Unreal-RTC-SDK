import {
  CXXFile,
  CXXParserConfigs,
  CXXTYPE,
  CXXTerraNode,
  Clazz,
  MemberFunction,
} from '@agoraio-extensions/cxx-parser';
import { fillParentNode_ForParseResult } from '@agoraio-extensions/cxx-parser/src/utils';
import { ParseResult, TerraContext } from '@agoraio-extensions/terra-core';

import {
  applyIrisApiId,
  getIrisApiIdValue,
} from '@agoraio-extensions/terra_shared_configs/src/parsers/iris_api_id_parser';
import {
  CommentConfig,
  CommentConfigKey,
  generateNodes,
  getConfigsFromComments,
} from '@agoraio-extensions/terra_shared_configs/src/utils/parser_utils';

export type OverrideNodeParserArgs = CXXParserConfigs & {
  customHeaderFileNamePrefix?: string;
  // Default is true, default override all nodes.
  overrideSourceNodes?: boolean;
};

export type OverrideNodeParserUserData = {
  sourceApiSignature: string;
  redirectIrisApiId: string;
  overridedNode: CXXTerraNode;
};

let filterCXXTypes = [CXXTYPE.IncludeDirective];

// Trim the namespace `ext` to match the existed node
function adjustNamespacesForCustomNode(myNode: CXXTerraNode) {
  myNode.namespaces = myNode.namespaces.filter((e) => e != 'ext');
}

export const OverrideNodeParser = (
  terraContext: TerraContext,
  args: OverrideNodeParserArgs,
  preParseResult?: ParseResult
): ParseResult | undefined => {
  let customHeaderFileNamePrefix = args.customHeaderFileNamePrefix ?? 'Custom';
  let overrideSourceNodes = args.overrideSourceNodes ?? true;
  const customNodes = generateNodes(terraContext, args, 'overridenode');
  let overrideCXXFiles = (customNodes?.nodes as CXXFile[]) ?? [];

  overrideCXXFiles
    .filter((file) => file.fileName.startsWith(customHeaderFileNamePrefix))
    .forEach((file) => {
      let overrideCXXFile = file as CXXFile;
      // Find existed file
      let existedFile = preParseResult?.nodes.find((it) => {
        let cxxFile = it as CXXFile;
        // The overrided file name can same as existed file name or be included in existed file name
        return (
          cxxFile.fileName === overrideCXXFile.fileName ||
          overrideCXXFile.fileName.includes(cxxFile.fileName)
        );
      });

      // Update the existed `CXXFile` if it exists
      if (existedFile) {
        let overrideNodes = overrideCXXFile.nodes;
        let overrideNodesFullNameMap: Map<string, _NodeHolder> = new Map();
        overrideNodes.forEach((node) => {
          adjustNamespacesForCustomNode(node);
          overrideNodesFullNameMap.set(node.fullName, new _NodeHolder(node));
        });

        for (let existedNode of (existedFile as CXXFile).nodes) {
          // Only override members for `Clazz` at this time
          if (!existedNode.isClazz()) {
            continue;
          }

          let overridedNode = overrideNodesFullNameMap.get(
            existedNode.fullName
          );

          // Nothing to override
          if (!overridedNode) {
            continue;
          }

          let clazz = existedNode.asClazz();

          if (!overrideSourceNodes) {
            annotateClazzMethods(clazz, overridedNode);
          } else {
            overrideClazzMethods(clazz, overridedNode);
          }
        }

        // Fill rest nodes to the existed file
        overrideNodesFullNameMap.forEach((value, _) => {
          if (!value.isVisited) {
            if (!filterCXXTypes.includes(value.value.__TYPE)) {
              // the rest node would be : struct
              // they would be used in the following method,
              // therefore, the order should be at the top, use [unshift] rather than [push]
              // Ex.
              // SDKBuildInfo
              // used in getVersion
              (existedFile as CXXFile).nodes.unshift(value.value);
            }
          }
        });
      } else {
        preParseResult?.nodes.push(file);
      }
    });

  // fix a node's parent pointer link
  fillParentNode_ForParseResult(preParseResult);

  return preParseResult;
};

function overrideClazzMethods(clazz: Clazz, overridedNode: _NodeHolder) {
  let newMethods: MemberFunction[] = [];
  let overrideMethodHoldersMap = new Map(
    overridedNode.value.asClazz().methods.map((method) => {
      adjustNamespacesForCustomNode(method);
      applyOverrideNodeParserUserData(clazz, method);
      return [method.name, new _NodeHolder(method)];
    })
  );

  for (let method of clazz.methods) {
    let overridedMethodHolder = overrideMethodHoldersMap.get(method.name);
    if (overridedMethodHolder) {
      if (!overridedMethodHolder.isVisited) {
        let overridedMethod = overridedMethodHolder.value as MemberFunction;
        newMethods.push(overridedMethod);
      }
    } else {
      newMethods.push(method);
    }
  }

  // Fill rest
  overrideMethodHoldersMap.forEach((value, _) => {
    if (!value.isVisited) {
      let overridedMethod = value.value as MemberFunction;
      newMethods.push(overridedMethod);
    }
  });

  clazz.methods = newMethods;
}

function annotateClazzMethods(clazz: Clazz, overridedNode: _NodeHolder) {
  let newMethods: MemberFunction[] = clazz.methods;
  let overrideMethodHoldersMap = new Map(
    overridedNode.value.asClazz().methods.map((method) => {
      adjustNamespacesForCustomNode(method);
      applyOverrideNodeParserUserData(clazz, method);
      let redirectIrisApiId =
        getOverrideNodeParserUserData(method)!.redirectIrisApiId;
      return [redirectIrisApiId, new _NodeHolder(method)];
    })
  );

  for (let method of newMethods) {
    let irisApiIdValue = getIrisApiIdValue(method);
    let overridedMethodHolder = overrideMethodHoldersMap.get(irisApiIdValue);
    if (overridedMethodHolder) {
      if (!overridedMethodHolder.isVisited) {
        let overridedMethod = overridedMethodHolder.value as MemberFunction;
        let overridedMethodApiIdValue = getIrisApiIdValue(overridedMethod);
        // If the overrided method's iris api id value is same, it means we only want to pin the specific method,
        // so we do not override the existed method.
        if (irisApiIdValue != overridedMethodApiIdValue) {
          method.user_data ??= {};
          method.user_data['OverrideNodeParser'] = {
            overridedNode: overridedMethod,
          };
        }
      }
    } else {
    }
  }

  // Fill rest
  overrideMethodHoldersMap.forEach((value, _) => {
    if (!value.isVisited) {
      let overridedMethod = value.value as MemberFunction;
      newMethods.push(overridedMethod as MemberFunction);
    }
  });

  clazz.methods = newMethods;
}

function applyOverrideNodeParserUserData(
  existedClazz: Clazz,
  customNode: CXXTerraNode
) {
  let configs: CommentConfig[] = getConfigsFromComments(customNode);
  let irisApiIdValue = '';
  let sourceApiSignature = '';
  let isGenerateIrisApiId = false;
  for (let config of configs) {
    switch (config.key) {
      case CommentConfigKey.SOURCE:
        sourceApiSignature = config.value;
        break;
      case CommentConfigKey.IRIS_API_ID:
        // get iris api id from comment key IRIS_API_ID
        irisApiIdValue = config.value;
        break;
      case CommentConfigKey.GENERATE_IRIS_API_ID:
        // This is no used now, but keep it for future usage.
        isGenerateIrisApiId = config.value === 'true';
        break;
    }
  }
  customNode.user_data ??= {};
  customNode.user_data['OverrideNodeParser'] = {
    sourceApiSignature: sourceApiSignature,
    redirectIrisApiId: irisApiIdValue,
  };
  applyIrisApiId(existedClazz, customNode as MemberFunction);
}

export function getOverrideNodeParserUserData(
  node: CXXTerraNode
): OverrideNodeParserUserData | undefined {
  return node.user_data?.['OverrideNodeParser'];
}

class _NodeHolder {
  private _isVisited: boolean = false;
  private _value: CXXTerraNode;

  constructor(value: CXXTerraNode) {
    this._value = value;
  }

  get value(): CXXTerraNode {
    this._isVisited = true;
    return this._value;
  }

  get isVisited(): boolean {
    return this._isVisited;
  }
}
