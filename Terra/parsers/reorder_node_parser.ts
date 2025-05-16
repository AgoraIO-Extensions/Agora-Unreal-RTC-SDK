import { CXXFile, CXXTYPE, Clazz } from '@agoraio-extensions/cxx-parser';
import { CXXTerraNode } from '@agoraio-extensions/cxx-parser';
import { ParseResult, TerraContext } from '@agoraio-extensions/terra-core';
import { BaseParserArgs } from '@agoraio-extensions/terra_shared_configs';

// TODO(littlegnal): Move to parser after https://jira.agoralab.co/browse/EP-488 is implemented
export function _ReorderNodes(
  parseResult: ParseResult,
  nodes: CXXTerraNode[]
): CXXTerraNode[] {
  let visitedNodes = new Map<CXXTerraNode, Set<CXXTerraNode>>();
  let newNodes = nodes;
  for (let i = 0; i < newNodes.length; i++) {
    let node = newNodes[i];
    if (!visitedNodes.has(node)) {
      visitedNodes.set(node, new Set<CXXTerraNode>());
    }

    if (node.__TYPE == CXXTYPE.Clazz || node.__TYPE == CXXTYPE.Struct) {
      (node as Clazz).member_variables.forEach((it) => {
        if (!it.type.is_builtin_type) {
          let foundNode = parseResult.resolveNodeByType(it.type);
          if (!visitedNodes.has(foundNode)) {
            visitedNodes.get(node)?.add(foundNode);
          }
        }
      });

      (node as Clazz).methods.forEach((it) => {
        it.parameters.forEach((it) => {
          if (!it.type.is_builtin_type) {
            let foundNode = parseResult.resolveNodeByType(it.type);
            if (!visitedNodes.has(foundNode)) {
              visitedNodes.get(node)?.add(foundNode);
            }
          }
        });
      });
    }
  }

  for (let key of visitedNodes.keys()) {
    if (visitedNodes.get(key)?.size == 0) {
      visitedNodes.delete(key);
    }
  }

  let reorderedNodes: CXXTerraNode[] = [];

  for (let key of visitedNodes.keys()) {
    let index = newNodes.findIndex((it) => it == key);

    visitedNodes.get(key)!.forEach((it) => {});

    let reorderNodes: CXXTerraNode[] = [];
    for (const v of visitedNodes.get(key)!) {
      if (!reorderedNodes.includes(v)) {
        reorderNodes.push(v);
      }
    }

    for (let n of reorderNodes) {
      let i = newNodes.findIndex((it) => it == n);
      if (i > index) {
        newNodes.splice(i, 1);
      }
    }

    newNodes = [
      ...newNodes.slice(0, index),
      ...reorderNodes,
      ...newNodes.slice(index),
    ];

    reorderedNodes = reorderedNodes.concat(reorderNodes);
  }

  return newNodes;
}

export function ReorderNodes(
  terraContext: TerraContext,
  args: BaseParserArgs,
  preParseResult?: ParseResult
): ParseResult | undefined {
  if (preParseResult) {
    let cxxfiles = preParseResult.nodes as CXXFile[];
    cxxfiles.forEach((cxxfile) => {
      cxxfile.nodes = _ReorderNodes(preParseResult, cxxfile.nodes);
    });
  }
  return preParseResult;
}
