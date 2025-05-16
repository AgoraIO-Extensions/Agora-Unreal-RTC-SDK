import * as path from 'path';

import { CXXFile, CXXTYPE, CXXTerraNode } from '@agoraio-extensions/cxx-parser';
import {
  ParseResult,
  RenderResult,
  TerraContext,
} from '@agoraio-extensions/terra-core';

import {
  IrisApiIdParserUserData,
  MustacheRenderConfiguration,
  renderWithConfiguration,
} from '@agoraio-extensions/terra_shared_configs';
import _ from 'lodash';

import * as UECodeFilter from '../utility/filter_helper';
import * as UECodeRender from '../utility/helper';

import * as Logger from '../utility/logger';
// prepare terra data for rendering

export function prepareTerraData(
  terraContext: TerraContext,
  args: any,
  parseResult: ParseResult
): any {
  const func_node_filter: UECodeRender.FilterTerraNodeFunction = (
    cxxfile: CXXFile
  ) => {
    // 筛选Node: IRtcEngine
    let nodes = cxxfile.nodes.filter((node: CXXTerraNode) => {
      return (
        node.__TYPE === CXXTYPE.Clazz &&
        (node.name === 'IRtcEngine' || node.name == 'IRtcEngineEx')
      );
    });
    return nodes;
  };

  const func_api_exclude: UECodeRender.ExcludeApiFunction = (
    method_name: string
  ) => {
    return UECodeFilter.UESDK_CheckIfApiExcluded(method_name);
  };

  let view = UECodeRender.genGeneralTerraData(
    terraContext,
    args,
    parseResult,
    func_node_filter,
    func_api_exclude
  );

  return UECodeRender.mergeAllNodesToOneCXXFile(view);
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
      'cppplugin',
      'AgoraUERtcEngine_impl_filename.mustache'
    ),

    fileContentTemplatePath: path.join(
      __dirname,
      '..',
      '..',
      'templates',
      'cppplugin',
      'AgoraUERtcEngine_impl_filecontent.mustache'
    ),
    view,
  };

  return renderWithConfiguration(one_render_config);
}
