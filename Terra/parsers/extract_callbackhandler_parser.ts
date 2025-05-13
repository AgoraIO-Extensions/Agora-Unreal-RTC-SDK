import { ParseResult, TerraContext } from '@agoraio-extensions/terra-core';
import { BaseParserArgs } from '@agoraio-extensions/terra_shared_configs';

export function ExtractCallbackHandler(
  terraContext: TerraContext,
  args: BaseParserArgs,
  preParseResult?: ParseResult
): ParseResult | undefined {
  return preParseResult;
}
