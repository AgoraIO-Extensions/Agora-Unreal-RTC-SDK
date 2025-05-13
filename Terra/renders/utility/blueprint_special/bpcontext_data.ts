// This is context data directly using in mustache template
export class BPStructContext {
  contextConstructor = '';
  contextCreateRawData = '';
  contextFreeRawData = '';

  constructor() {
    this.contextConstructor = '';
    this.contextCreateRawData = '';
    this.contextFreeRawData = '';
  }
}

export class BPParamContext {
  contextDecl = '';
  contextUsage = '';
  contextFree = '';

  constructor() {
    this.contextDecl = '';
    this.contextUsage = '';
    this.contextFree = '';
  }
}

export class BPMethodContext {
  contextParam_CppFromBP = new BPParamContext();
  contextParam_BPFromCpp = new BPParamContext();

  // Because in bp method:
  // 1. if it has macro scope, it always has method, but have no cpp native method.
  contextReturnValBegin = '';
  contextReturnValSetVal = '';
  contextReturnValEnd = '';
  constructor() {
    this.contextParam_CppFromBP = new BPParamContext();
    this.contextParam_BPFromCpp = new BPParamContext();
    this.contextReturnValBegin = '';
    this.contextReturnValSetVal = '';
    this.contextReturnValEnd = '';
  }
}
