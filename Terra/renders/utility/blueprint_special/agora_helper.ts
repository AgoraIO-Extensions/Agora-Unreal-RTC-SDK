import { SimpleType } from '@agoraio-extensions/cxx-parser';

export function IsAgoraProject(): boolean {
  return true;
}

export function isAgoraClassType(type: SimpleType): boolean {
  // TBD(WinterPu):
  // Custom Header would add namespace ext Ex. agora::rtc::ext::AudioDeviceInfo
  // Notice: AudioDeviceInfo is defined in custom headers
  return type.name.toLowerCase().includes('::ext::');
}
