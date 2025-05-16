import path from 'path';

import { start } from 'repl';

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
import { List, map } from 'lodash';

import { map_macrop_scope_makeup } from './blueprint_special/bptype_data_makeup';
import * as Tools from './tools';
export function formatAsCppComment(input: string): string {
  if (input == '' || input == undefined) {
    return '';
  }

  // 去掉首尾空格和换行
  const trimmedInput = input.trim();

  // 将每行前加 *，并包裹在 /* 和 */
  const commentLines = trimmedInput
    .split('\n')
    .map((line) => ` * ${line}`)
    .join('\n');

  return `/*\n${commentLines}\n */`;
}

export function prettyDefaultValue(
  parseResult: ParseResult,
  defaultValueType: SimpleType,
  defaultValue: string
): string {
  let out = defaultValue;
  if (defaultValue.length == 0) {
    return out;
  }
  let tmpDefaultValueNode = parseResult.resolveNodeByType(defaultValueType);
  if (
    tmpDefaultValueNode.__TYPE == CXXTYPE.Struct ||
    tmpDefaultValueNode.__TYPE == CXXTYPE.Clazz
  ) {
    out = `${tmpDefaultValueNode.fullName}()`;
  } else if (tmpDefaultValueNode.__TYPE == CXXTYPE.Enumz) {
    let tmpName = defaultValue
      .replaceAll('(', '')
      .replaceAll(')', '')
      .split('::')
      .pop();
    out = `${tmpDefaultValueNode.fullName}::${tmpName}`;
  }

  if (out == '__null') {
    out = 'nullptr';
  }

  return out;
}

export function createCompilationDirectivesContent(
  node: CXXTerraNode,
  isStart: boolean = true
): string {
  // TBD(WinterPu)
  // should be moved to bp helper.
  const data_macrop_scope = map_macrop_scope_makeup[node.fullName];
  if (data_macrop_scope) {
    return isStart ? data_macrop_scope.start : data_macrop_scope.end;
  }

  let directives = node.conditional_compilation_directives_infos;
  if (directives.length == 0) {
    return '';
  }

  let startIf = directives.join('\n');
  startIf = startIf === '\n' ? '' : startIf;
  if (isStart) {
    return startIf;
  }

  let endIf = directives.map((it) => '\n#endif').join('');
  return endIf;
}

export function IsDeprecatedAttr(str_attribute: string): boolean {
  return str_attribute === '__deprecated__' || str_attribute === 'deprecated';
}

export function genSuffixAttribute(input: string[]): string {
  if (input.length <= 0) return '';

  let str_attribute = '';
  input.forEach((attr) => {
    if (IsDeprecatedAttr(attr)) {
      str_attribute = '__deprecated';
    }
  });
  return str_attribute;
}

export function getFileName(cxxFile: CXXFile): string {
  return Tools.extractFileName(cxxFile.file_path);
}

export function isCallbackClazz(node: CXXTerraNode): boolean {
  return (
    node.__TYPE === CXXTYPE.Clazz && Tools.isMatch(node.name, 'isCallback')
  );
}
