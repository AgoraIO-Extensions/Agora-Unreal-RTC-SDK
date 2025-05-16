import * as Logger from './logger';

export const map_failure_return_val: Record<string, string> = {
  'int': 'AGORA_UE_ERR_CODE(ERROR_NULLPTR)',
  'char const*': 'nullptr',
  'bool': 'false',
  'agora_refptr': 'nullptr',
  'agora::rtc::video_track_id_t': '0',
  'float': '0.0f',
  'agora::rtc::IScreenCaptureSourceList*': 'nullptr',
  'agora::rtc::CONNECTION_STATE_TYPE':
    'agora::rtc::CONNECTION_STATE_TYPE::CONNECTION_STATE_FAILED',
  'int64_t': '0',
  'uint64_t': '0',
  'agora_refptr<agora::rtc::IMediaPlayer>': 'nullptr',
  'agora_refptr<agora::rtc::IMediaRecorder>': 'nullptr',
  'void': '',

  // // TBD(WinterPu) They are in AgoraBPuAgoraMediaBase.cpp
  // 'int64': '0',
  // 'EUABT_VIDEO_FRAME_PROCESS_MODE':
  //   'EUABT_VIDEO_FRAME_PROCESS_MODE::PROCESS_MODE_READ_WRITE',
  // 'EUABT_VIDEO_PIXEL_FORMAT': 'EUABT_VIDEO_PIXEL_FORMAT::VIDEO_PIXEL_DEFAULT',
};

const list_custom_impl_methods = [
  'initialize',
  'setupRemoteVideo',
  'setupLocalVideo',
  'setupRemoteVideoEx',
  'writeLog',
];

export function UESDK_CheckIfApiExcluded(method_name: string): boolean {
  // console.log(`method_name: ${method_name} is excluded: ${list_custom_impl_methods.includes(method_name)}`);
  return list_custom_impl_methods.includes(method_name);
}

export function UESDK_GetFailureReturnVal(
  return_type: string
): string | undefined {
  const returnValue = map_failure_return_val[return_type];

  if (returnValue === undefined) {
    Logger.PrintError(`Error: No value found for return type "${return_type}"`);
  }

  return returnValue;
}
