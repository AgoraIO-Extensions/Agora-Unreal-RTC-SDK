export type ClazzMethodReplacedContext_ = {
  doReplceDecl: boolean;
  declOp_IncludingComments: boolean;
  decl: string;
  doReplceImpl: boolean;
  impl: string;
  description: string;
};

export const rc_empty_data: ClazzMethodReplacedContext_ = {
  doReplceDecl: false,
  declOp_IncludingComments: false,
  decl: ``,
  doReplceImpl: false,
  impl: ``,
  description: ``,
};

// all data map
const _map_data_replaced_context: {
  [key: string]: ClazzMethodReplacedContext_;
} = {};

// register module: avoid duplicate registration
const registeredModules = new Set<string>();
let isInitialized = false;

const dir_name = 'agora_data';

export function registerMapData(
  mapData: {
    [key: string]: ClazzMethodReplacedContext_;
  },
  moduleName?: string
): void {
  if (moduleName && registeredModules.has(moduleName)) {
    return;
  }

  Object.entries(mapData).forEach(([key, value]) => {
    _map_data_replaced_context[key] = value;
  });

  if (moduleName) {
    registeredModules.add(moduleName);
  }
}

function initializeAllModules(): void {
  if (isInitialized) return;
  isInitialized = true;

  try {
    // 使用Node.js的fs模块读取./data目录下的所有文件
    const fs = require('fs');
    const path = require('path');

    try {
      const dataDir = path.resolve(__dirname, dir_name);
      const files = fs.readdirSync(dataDir);
      // filter all .ts files
      const tsFiles = files.filter((file: string) => file.endsWith('.ts'));

      // import each file and register its [map_data]
      for (const file of tsFiles) {
        // get module name (remove .ts suffix)
        const moduleName = file.replace('.ts', '');

        if (!registeredModules.has(moduleName)) {
          try {
            // build module path (relative path)
            const modulePath = `./${dir_name}/${moduleName}`;
            const module = require(modulePath);

            if (module && module.map_data) {
              registerMapData(module.map_data, moduleName);
              console.log(`Registered module: ${moduleName}`);
            } else {
              console.log(`Module ${moduleName} does not export map_data`);
            }
          } catch (e) {
            console.error(`Failed to import ${moduleName}:`, e);
          }
        }
      }
    } catch (e) {
      console.error('Error reading data directory:', e);

      // fallback: if failed to read directory, then use known modules list
      fallbackToKnownModules();
    }
  } catch (e) {
    console.error('Error initializing modules:', e);

    // fallback: if fs module is not available, then use known modules list
    fallbackToKnownModules();
  }
}

// fallback: use known modules list
function fallbackToKnownModules(): void {
  console.log('Falling back to known modules list');

  // list all possible modules
  const possibleModules = [
    'IRtcEngine',
    'IRtcEngine2',
    'IAudioDeviceManager',
    'IMediaEngine',
    'IMediaPlayer',
    'ILocalSpatialAudioEngine',
    'IMusicContentCenter',
    'IMusicPlayer',
    'IVideoDeviceManager',
    'IRtcEngineEx',
    'IRtcEngineEvent',
  ];

  for (const moduleName of possibleModules) {
    if (!registeredModules.has(moduleName)) {
      try {
        // try to import module
        const module = require(`./${dir_name}/${moduleName}`);

        if (module && module.map_data) {
          registerMapData(module.map_data, moduleName);
          console.log(`Registered module using fallback: ${moduleName}`);
        }
      } catch (e) {
        // ignore import failed error, because we are trying to register possible modules
      }
    }
  }
}

export function getMapDataMethodReplacedContext(): {
  [key: string]: ClazzMethodReplacedContext_;
} {
  // ensure initialized (synchronously)
  if (!isInitialized) {
    initializeAllModules();
  }

  return _map_data_replaced_context;
}

// provide a function to manually register a specific module
export function registerModule(moduleName: string): boolean {
  if (registeredModules.has(moduleName)) {
    return true; // already registered
  }

  try {
    const module = require(`./${dir_name}/${moduleName}`);

    if (module && module.map_data) {
      registerMapData(module.map_data, moduleName);
      return true;
    }
    return false;
  } catch (e) {
    console.error(`Failed to import module ${moduleName}:`, e);
    return false;
  }
}

// immediately initialize
initializeAllModules();
