import path from 'path';

import { CXXTerraNode } from '@agoraio-extensions/cxx-parser';

import { AGORA_MUSTACHE_DATA } from './blueprint_special/bptype_mustache_data';

const regMap: { [key: string]: string } = {
  isCallback: '.*(Observer|Handler|Callback|Receiver|Sink).*',
};

export function isMatch(str: string, type: string): boolean {
  let result = false;
  if (regMap[type]) {
    result = new RegExp(regMap[type]).test(str);
  }
  return result;
}

export function convertTypeNameToNodeName(input: string): string {
  if (!input) return input; // handle undefined
  return removeNamespace(input);
}

export function removeNamespace(input: string): string {
  if (!input) return input; // handle undefined
  // use regular expression to remove namespace
  return input.replace(/.*::/, '');
}

export function isNullOrEmpty(str: string | null | undefined): boolean {
  // including whitespace
  return str === null || str === undefined || str.trim() === '';
}

export function addOneLine_Format(
  line: string,
  prefix_indent: string = ''
): string {
  return prefix_indent + line + '\n';
}

export function IsNotEmptyStr(str: string | undefined): boolean {
  return str !== null && str !== undefined && str.trim() !== '';
}

export function IsOptionalUABTType(type: string): boolean {
  return type.startsWith(AGORA_MUSTACHE_DATA.FUABT_OPT_PREFIX);
}

export function extractFileName(file_path: string): string {
  return path.basename(file_path, path.extname(file_path));
}

export function extractBracketNumber(input: string): string {
  const match = input.match(/\[(\d+)\]/);
  return match ? match[1] : '';
}

/**
 * Removes C++ type attributes like 'const', 'volatile', 'restrict', etc.,
 * but preserves the core type name and pointer/reference symbols.
 *
 * @example
 * // Returns "char*"
 * removeAttributes("const char* const");
 *
 * @example
 * // Returns "MyClass*"
 * removeAttributes("const MyClass* volatile");
 *
 * @param typeStr The C++ type string to clean
 * @returns The cleaned type string with only the core type and pointer/reference symbols
 */
export function removeAttributes(typeStr: string): string {
  if (!typeStr) return typeStr;

  // // Step 1: Remove namespace if any
  // let result = removeNamespace(typeStr);

  let result = typeStr;

  // Step 2: Remove common C++ type attributes
  const attributesToRemove = [
    /\bconst\b/g,
    /\bvolatile\b/g,
    /\brestrict\b/g,
    /\bmutable\b/g,
    /\bstatic\b/g,
    /\bextern\b/g,
    /\bregister\b/g,
    /\bauto\b/g,
    /\binline\b/g,
    /\bexplicit\b/g,
    /\b__restrict\b/g,
  ];

  attributesToRemove.forEach((attr) => {
    result = result.replace(attr, '');
  });

  // Step 3: Clean up multiple spaces and normalize spacing
  result = result.replace(/\s+/g, ' ').trim();

  // Step 4: Fix spacing around pointers/references
  // Remove spaces between type and pointer/reference
  result = result.replace(/\s+([*&])/g, '$1');

  // Step 5: Remove spaces between consecutive pointers/references
  result = result.replace(/([*&])\s+([*&])/g, '$1$2');

  return result;
}

export function isNumeric(str: string): boolean {
  // 如果为空，非字符串或只有空格，则不是数字
  if (!str || typeof str !== 'string' || str.trim() === '') {
    return false;
  }

  // 移除前后空格
  const trimmedStr = str.trim();

  // 使用isNaN和Number转换检查是否为数字
  // 注意：isNaN("123") 返回 false，因为 "123" 可以转换为数字
  // isNaN("abc") 返回 true，因为 "abc" 不能转换为数字
  const numValue = Number(trimmedStr);

  // !isNaN(numValue) 检查它是一个有效的数字
  // isFinite(numValue) 确保它不是 Infinity 或 -Infinity
  return !isNaN(numValue) && isFinite(numValue);
}
