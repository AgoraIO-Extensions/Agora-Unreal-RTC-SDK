import {
  CXXFile,
  CXXTYPE,
  CXXTerraNode,
  MemberFunction,
} from '@agoraio-extensions/cxx-parser';
import { ParseResult, TerraContext } from '@agoraio-extensions/terra-core';

import { MergeNodeConfig } from '@agoraio-extensions/terra_shared_configs/configs/rtc/merge_node_list';

import {
  BaseParserArgs,
  adjustIrisApiIdKeyIfNeeded,
  adjustIrisApiIdValueIfNeeded,
} from '@agoraio-extensions/terra_shared_configs/src/index';
import { getConfigs } from '@agoraio-extensions/terra_shared_configs/src/utils/parser_utils';

const defaultConfig = require('@agoraio-extensions/terra_shared_configs/configs/rtc/merge_node_list.ts');

export function ResolveMergedNodeDependencies(
  sourceFile: CXXFile | undefined,
  targetFile: CXXFile | undefined,
  sourceClazz: CXXTerraNode | undefined,
  targetClazz: CXXTerraNode | undefined
) {
  if (!sourceFile || !targetFile || !sourceClazz || !targetClazz) {
    return;
  }
  // move sourceClazz dependency
  let visitedNodes = new Set<string>();
  const deletedSourceNodes = new Set<CXXTerraNode>();
  targetFile?.nodes.forEach((node) => {
    if (node.__TYPE === CXXTYPE.Clazz && node.name === targetClazz.name) {
      node.asClazz().methods.forEach((method) => {
        method.parameters.forEach((param) => {
          if (!param.type.is_builtin_type) {
            visitedNodes.add(param.type.name);
          }
        });
      });
    }
  });
  sourceFile?.nodes.forEach((node) => {
    if (visitedNodes.has(node.fullName)) {
      targetFile?.nodes.unshift(node);
      deletedSourceNodes.add(node);
    }
  });

  for (let node of deletedSourceNodes) {
    console.log('remove node' + node.fullName);
  }
  sourceFile!.nodes = sourceFile!.nodes.filter(
    (node) => !deletedSourceNodes.has(node)
  );
}

export interface MergeNodeParserUserData {
  sourceClazzName: string;
}

export function MergeNodeParser(
  terraContext: TerraContext,
  args: BaseParserArgs,
  preParseResult?: ParseResult
): ParseResult | undefined {
  const configs: MergeNodeConfig[] = getConfigs(
    {
      ...args,
      defaultConfig: defaultConfig,
    },
    terraContext
  );

  if (preParseResult) {
    for (let config of configs) {
      let sourceClazz: CXXTerraNode | undefined = undefined;
      let targetClazz: CXXTerraNode | undefined = undefined;

      let sourceFile: CXXFile | undefined = undefined;
      let targetFile: CXXFile | undefined = undefined;

      for (
        let fileIndex = 0;
        fileIndex < preParseResult.nodes.length;
        fileIndex++
      ) {
        let file = preParseResult.nodes[fileIndex] as CXXFile;
        if (!sourceClazz) {
          for (let index = 0; index < file.nodes.length; index++) {
            if (file.nodes[index]?.fullName === config.source) {
              sourceClazz = file.nodes[index];
              sourceFile = file;
              //根据deleteSource来决定找到后是否删除source
              if (config.deleteSource) {
                // delete file.nodes[index];
                file.nodes.splice(index, 1);
              }
              break;
            }
          }
        }
        if (!targetClazz) {
          for (let node of file.nodes) {
            if (node?.fullName === config.target) {
              targetClazz = node;
              targetFile = file;
              break;
            }
          }
        }
        if (sourceClazz && targetClazz) {
          break;
        }
      }
      if (sourceClazz && targetClazz) {
        let isFilterOverloadFunctions =
          config.isFilterOverloadFunctions ?? true;
        if (isFilterOverloadFunctions) {
          targetClazz!.asClazz().methods.map((tar_method, tar_index) => {
            for (let i = 0; i < sourceClazz!.asClazz().methods.length; i++) {
              let sou_method = sourceClazz!.asClazz().methods[i];
              if (tar_method.name === sou_method.name) {
                let tarMethodParent = tar_method.parent;
                let tarMethodParentName = tar_method.parent_name;
                targetClazz!.asClazz().methods[tar_index] = sou_method;
                // Fix the relationship.
                targetClazz!.asClazz().methods[tar_index].parent =
                  tarMethodParent;
                targetClazz!.asClazz().methods[tar_index].parent_name =
                  tarMethodParentName;

                adjustIrisApiIdKeyIfNeeded(
                  targetClazz!.asClazz(),
                  targetClazz!.asClazz().methods[tar_index]
                );
                adjustIrisApiIdValueIfNeeded(
                  targetClazz!.asClazz(),
                  targetClazz!.asClazz().methods[tar_index]
                );

                applyMergeNodeParserUserData(
                  targetClazz!.asClazz().methods[tar_index],
                  sourceClazz!.asClazz().name
                );
                break;
              }
            }
          });
        } else {
          targetClazz!.asClazz().methods = [
            ...targetClazz!.asClazz().methods,
            ...sourceClazz!.asClazz().methods,
          ].map((it) => {
            // Fix the relationship.
            it.parent = targetClazz;
            //it.parent_name = targetClazz?.fullName ?? '';
            // Since original parent name is without namespace
            it.parent_name = targetClazz?.name ?? '';
            adjustIrisApiIdKeyIfNeeded(targetClazz!.asClazz(), it);
            adjustIrisApiIdValueIfNeeded(targetClazz!.asClazz(), it);

            return it;
          });

          sourceClazz!.asClazz().methods.forEach((method) => {
            applyMergeNodeParserUserData(method, sourceClazz!.asClazz().name);
          });
        }
      }

      // Resolve Dependency
      ResolveMergedNodeDependencies(
        sourceFile,
        targetFile,
        sourceClazz,
        targetClazz
      );
    }
  }
  return preParseResult;
}

function applyMergeNodeParserUserData(
  method: MemberFunction,
  sourceClazzName: string
) {
  method.user_data ??= {};
  method.user_data['MergeNodeParser'] = {
    sourceClazzName: sourceClazzName,
  } as MergeNodeParserUserData;
}

export function getMergeNodeParserUserData(
  node: CXXTerraNode
): MergeNodeParserUserData | undefined {
  return node.user_data?.['MergeNodeParser'] as
    | MergeNodeParserUserData
    | undefined;
}
