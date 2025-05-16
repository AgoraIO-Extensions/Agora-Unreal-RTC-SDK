import * as path from 'path';

import { CXXFile, CXXTYPE, CXXTerraNode } from '@agoraio-extensions/cxx-parser';
import {
  ParseResult,
  RenderResult,
  TerraContext,
} from '@agoraio-extensions/terra-core';

import {
  MustacheRenderConfiguration,
  renderWithConfiguration,
} from '@agoraio-extensions/terra_shared_configs';
import _ from 'lodash';

import * as UECodeRender from '../utility/helper';

import * as Logger from '../utility/logger';

// prepare terra data for rendering

export function prepareTerraData(
  terraContext: TerraContext,
  args: any,
  parseResult: ParseResult
): any {
  return UECodeRender.genGeneralTerraData(terraContext, args, parseResult);
}

// call api to render
export default function (
  terraContext: TerraContext,
  args: any,
  parseResult: ParseResult
): RenderResult[] {
  let name_renderer = __filename;
  Logger.PrintStageLog(name_renderer);
  let originalParseResult = _.cloneDeep(parseResult);
  let view = prepareTerraData(terraContext, args, originalParseResult);

  const one_render_config: MustacheRenderConfiguration = {
    fileNameTemplatePath: path.join(
      __dirname,
      '..',
      '..',
      'templates',
      'bpplugin',
      'bp_impl_filename.mustache'
    ),
    fileContentTemplatePath: path.join(
      __dirname,
      '..',
      '..',
      'templates',
      'bpplugin',
      'bp_impl_filecontent.mustache'
    ),
    view,
  };

  return renderWithConfiguration(one_render_config);
}
