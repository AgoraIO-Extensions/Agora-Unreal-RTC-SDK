import { CXXFile, CXXTYPE, CXXTerraNode } from '@agoraio-extensions/cxx-parser';
import { ParseResult, TerraContext } from '@agoraio-extensions/terra-core';

import { BaseParserArgs } from '@agoraio-extensions/terra_shared_configs';
import { getConfigs } from '@agoraio-extensions/terra_shared_configs/src/utils/parser_utils';

const defaultConfig = require('@agoraio-extensions/terra_shared_configs/configs/rtc/remove_node_list');

function filterNode<T extends CXXTerraNode>(
  nodes: T[],
  name_configs: string[],
  regex_configs: string[]
): T[] {
  return nodes.filter((node) => {
    var flag = true;
    if (name_configs.includes(node.fullName)) {
      // 配置表中配置了该node则过滤掉
      flag = false;
    }
    regex_configs.forEach((v) => {
      const regex = new RegExp(v);
      if (regex.test(node.realName)) {
        // 满足正则表达式则过滤掉
        flag = false;
      }
    });
    return flag;
  });
}

export function RemoveNodeParser(
  terraContext: TerraContext,
  args: BaseParserArgs,
  preParseResult?: ParseResult
): ParseResult | undefined {
  const configs = getConfigs(
    {
      ...args,
      defaultConfig: defaultConfig,
    },
    terraContext
  );
  //remove file with .h
  let file_configs = configs.filter((v: string) => v.endsWith('.h'));
  if (file_configs?.length > 0 && preParseResult?.nodes) {
    preParseResult.nodes = preParseResult.nodes.filter((f) => {
      return !file_configs.includes((f as CXXTerraNode).fileName);
    });
  }
  let name_configs = configs.filter(
    (v: string) => !v.startsWith('^') && !v.endsWith('$')
  );
  let regex_configs = configs.filter(
    (v: string) => v.startsWith('^') || v.endsWith('$')
  );
  preParseResult?.nodes.forEach((f) => {
    let file = f as CXXFile;
    file.nodes = filterNode(file.nodes, name_configs, regex_configs);
    file.nodes.forEach((node) => {
      if (node.__TYPE === CXXTYPE.Struct) {
        node.asStruct().member_variables = filterNode(
          node.asStruct().member_variables,
          name_configs,
          regex_configs
        );
      } else if (node.__TYPE === CXXTYPE.Clazz) {
        node.asClazz().base_clazzs = filterNode(
          node.asClazz().base_clazzs.map((v) => {
            return { fullName: v } as CXXTerraNode;
          }),
          name_configs,
          regex_configs
        ).map((v) => v.fullName);
        node.asClazz().member_variables = filterNode(
          node.asClazz().member_variables,
          name_configs,
          regex_configs
        );
        node.asClazz().methods = filterNode(
          node.asClazz().methods,
          name_configs,
          regex_configs
        );
        node.asClazz().methods.forEach((method) => {
          method.parameters = filterNode(
            method.parameters,
            name_configs,
            regex_configs
          );
        });
      }
    });
  });
  return preParseResult;
}
