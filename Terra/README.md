# Terra - Blueprint


## Before committing
```
npm run test // unit test
npm run lint // format
```

## Quick Start
```
mkdir -p packages/cpp
mkdir -p packages/blueprint
bash build.sh
```


# terra

terra is a shell of the code-gen flow: Parse AST -> Generate codes.

**Disclaimer**: This is not an officially supported Agora product.

## Preparation

### Prerequisites

[node](https://nodejs.org/en/download) >=18

[yarn](https://classic.yarnpkg.com/lang/en/docs/install/#mac-stable)

Additional setup required for using [cxx-parser](cxx-parser/README.md#prerequisites)

## Getting Started

### Installing terra in your Project

> Currently, we do not provide an npm package for this repository. You should depend on `terra` from the GitHub repository using [yarn berry](https://github.com/yarnpkg/berry) as the package manager.

#### 1. Create a `.yarnrc.yml` file in your project directory:

```
echo "nodeLinker: node-modules" >> .yarnrc.yml
```

#### 2. Set `yarn` version to `berry`:

`yarn set version berry`

#### 3. Install `terra` from the GitHub repository:

```
yarn add <terra repo url>
# yarn add git@github.com:AgoraIO-Extensions/terra.git#head=main&workspace=terra
# yarn add git@github.com:AgoraIO-Extensions/terra.git#head=main&workspace=terra-core
```

#### 4. Install dependencies:

`yarn`

### Configuration Format

The terra configuration uses a YAML format. Here's an example:

```yaml
# List of parser configurations
parsers:
  # Configuration for the first parser
  - name: 'my-custom-parser' # Name of the parser, optional
    package: 'parser-package-name' # Package name where the parser is located
    # path: 'relative/path/to/parser' # Or specify the relative path to the parser
    args: # Arguments to pass to the parser
      option1: 'value1'
      option2: 'value2'

  # Configuration for the second parser
  - name: 'default-parser' # Default export parser, name can be omitted
    path: 'relative/path/to/default-parser'
    # package: 'another-parser-package' # Or specify the package name
    args:
      setting1: 'abc'
      setting2: 123

# List of renderer configurations
renderers:
  # Configuration for the first renderer
  - name: 'example-renderer'
    package: 'renderer-package-name'
    args:
      param1: 'foo'
      param2: 'bar'

  # Configuration for the second renderer
  - path: 'path/to/another-renderer'
    args:
      config1: true
      config2: 'xyz'
```

### Custom `Parser` and `Renderer`

#### Writing a `Parser`

```ts
import {
  ParseResult,
  TerraContext,
  TerraNode,
} from '@agoraio-extensions/terra-core';

export interface MyTerraNode extends TerraNode {
  myProperty1: string;
  myProperty2: string;
}

export default function MyParser(
  terraContext: TerraContext,
  args: any,
  parseResult?: ParseResult
): ParseResult | undefined {
  let myTerraNode = {
    myProperty1: 'myProperty1',
    myProperty2: 'myProperty2',
  } as MyTerraNode;
  let myParserResult = new ParseResult();
  myParserResult.nodes = [myTerraNode];
  return myParserResult;
}
```

### Writing a `Renderer`

```ts
import { ParseResult, RenderResult } from '@agoraio-extensions/terra-core';

import { MyTerraNode } from './test_parser';

export default function (parseResult: ParseResult): RenderResult[] {
  let fileContent = parseResult.nodes
    .map((node) => {
      let myTerraNode = node as MyTerraNode;
      return `${myTerraNode.myProperty1}\n${myTerraNode.myProperty2}`;
    })
    .join('\n');

  return [{ file_name: 'test_renderer.txt', file_content: fileContent }];
}
```

### Running `terra`

Add a config file (e.g., `my_terra_config.yaml``) and execute terra:

```yaml
# my_terra_config.yaml
parsers:
  - path: test_parser.ts

renderers:
  - path: test_renderer.ts
```

```
npm exec terra -- run --config my_terra_config.yaml --output-dir=<YOUR_OUTPUT_PATH>
```

## Examples

- https://github.com/AgoraIO-Extensions/iris_web/blob/main/scripts/terra
- https://github.com/AgoraIO-Extensions/Agora-Flutter-SDK/tree/main/tool/terra

## License

The project is under the MIT license.





## Usage

```
bash build.sh
// or use: quick build
bash qbuild.sh 
```