export enum LogLevel {
  Silent = 0,
  Error = 1,
  Warn = 2,
  Info = 3,
  Debug = 4,
}

const logLevel = LogLevel.Silent;

export function Print(message: string): void {
  if (logLevel >= LogLevel.Debug) {
    console.log(message);
  }
}

export function PrintStageLog(message: string): void {
  if (logLevel >= LogLevel.Info) {
    console.log(` ============ UESDKLog - Stage: ${message} ============ `);
  }
}

export function PrintError(message: string): void {
  if (logLevel >= LogLevel.Error) {
    console.error(`[*** UESDKError ***]: ${message}`);
  }
}

export function PrintWarn(message: string): void {
  if (logLevel >= LogLevel.Warn) {
    console.warn(`[*** UESDKWarning ***]: ${message}`);
  }
}
