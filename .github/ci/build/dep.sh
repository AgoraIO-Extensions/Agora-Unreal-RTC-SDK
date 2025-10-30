#!/bin/bash
set -e
set +x
MY_PATH=$(realpath $(dirname "$0"))
PROJECT_ROOT=$(realpath ${MY_PATH}/../../..)
URL_JSON_PATH="${PROJECT_ROOT}/Agora-Unreal-SDK-CPP/AgoraPlugin/Resources/url.json"

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <json_input>"
    exit 1
fi
INPUT=$1

IOS_DEPENDENCIES=$(echo "$INPUT" | jq -r '.[] | select(.platform == "iOS") | .cdn[]')
MAC_DEPENDENCIES=$(echo "$INPUT" | jq -r '.[] | select(.platform == "macOS") | .cdn[]')
ANDROID_DEPENDENCIES=$(echo "$INPUT" | jq -r '.[] | select(.platform == "Android") | .cdn[]')
WINDOWS_DEPENDENCIES=$(echo "$INPUT" | jq -r '.[] | select(.platform == "Windows") | .cdn[]')

# Extract version from first platform that has a non-empty version
DEP_VERSION=$(echo "$INPUT" | jq -r '.[] | select(.version != "" and .version != null) | .version' | head -n 1)
echo "Detected version: $DEP_VERSION"

# Helper: detect release type from dependency URLs (video|audio), default video
detect_release_type() {
  local list="$1"
  local has_video=0
  local has_audio=0
  for DEP in $list; do
    case "$DEP" in
      *Video*) has_video=1 ;;
      *Audio*|*Voice*) has_audio=1 ;;
    esac
  done
  if [ "$has_video" = "1" ] && [ "$has_audio" != "1" ]; then
    echo video
  elif [ "$has_audio" = "1" ] && [ "$has_video" != "1" ]; then
    echo audio
  else
    echo video
  fi
}

# Determine global RELEASE_TYPE from all native SDK links
RELEASE_TYPE=$(detect_release_type "$IOS_DEPENDENCIES $ANDROID_DEPENDENCIES $MAC_DEPENDENCIES $WINDOWS_DEPENDENCIES")
echo "Detected release type: $RELEASE_TYPE"

# Helper: choose first native link from cdn list
choose_native_dep() {
  local list="$1"
  for DEP in $list; do
    echo "$DEP"; return
  done
  echo ""
}

# Helper: update url.json using jq
update_url_json() {
  local release_type="$1"   # video | audio
  local platform="$2"       # native_win | native_mac | native_android | native_ios
  local value="$3"          # url value
  
  [ -z "$value" ] && return 0
  
  if [ ! -f "$URL_JSON_PATH" ]; then
    echo "url.json not found at $URL_JSON_PATH"
    return 1
  fi
  
  echo "Updating .$release_type.$platform with value: $value"
  
  # Update the JSON file
  jq --arg val "$value" ".$release_type.$platform = \$val" "$URL_JSON_PATH" > "$URL_JSON_PATH.tmp"
  
  if [ $? -eq 0 ]; then
    mv "$URL_JSON_PATH.tmp" "$URL_JSON_PATH"
    echo "Successfully updated .$release_type.$platform to: $value"
  else
    echo "Failed to update .$release_type.$platform"
    rm -f "$URL_JSON_PATH.tmp"
    return 1
  fi
}

# Process Windows dependencies
if [ -z "$WINDOWS_DEPENDENCIES" ]; then
  echo "No windows native dependencies need to change."
else
  NATIVE_WIN=$(choose_native_dep "$WINDOWS_DEPENDENCIES")
  if [ -n "$NATIVE_WIN" ]; then
    echo "Windows native dependency: $NATIVE_WIN"
    if [ "$RELEASE_TYPE" = "audio" ]; then
      update_url_json audio native_win "$NATIVE_WIN"
    else
      update_url_json video native_win "$NATIVE_WIN"
    fi
  fi
fi

# Process macOS dependencies
if [ -z "$MAC_DEPENDENCIES" ]; then
  echo "No mac native dependencies need to change."
else
  NATIVE_MAC=$(choose_native_dep "$MAC_DEPENDENCIES")
  if [ -n "$NATIVE_MAC" ]; then
    echo "Mac native dependency: $NATIVE_MAC"
    if [ "$RELEASE_TYPE" = "audio" ]; then
      update_url_json audio native_mac "$NATIVE_MAC"
    else
      update_url_json video native_mac "$NATIVE_MAC"
    fi
  fi
fi

# Process iOS dependencies
if [ -z "$IOS_DEPENDENCIES" ]; then
  echo "No iOS native dependencies need to change."
else
  NATIVE_IOS=$(choose_native_dep "$IOS_DEPENDENCIES")
  if [ -n "$NATIVE_IOS" ]; then
    echo "iOS native dependency: $NATIVE_IOS"
    if [ "$RELEASE_TYPE" = "audio" ]; then
      update_url_json audio native_ios "$NATIVE_IOS"
    else
      update_url_json video native_ios "$NATIVE_IOS"
    fi
  fi
fi

# Process Android dependencies
if [ -z "$ANDROID_DEPENDENCIES" ]; then
  echo "No Android native dependencies need to change."
else
  NATIVE_ANDROID=$(choose_native_dep "$ANDROID_DEPENDENCIES")
  if [ -n "$NATIVE_ANDROID" ]; then
    echo "Android native dependency: $NATIVE_ANDROID"
    if [ "$RELEASE_TYPE" = "audio" ]; then
      update_url_json audio native_android "$NATIVE_ANDROID"
    else
      update_url_json video native_android "$NATIVE_ANDROID"
    fi
  fi
fi

# Increment Build number in url.json
if [ -f "$URL_JSON_PATH" ]; then
  echo "Incrementing Build number in url.json..."
  
  # Read current build number
  BUILD_NUM=$(jq -r '.version.build' "$URL_JSON_PATH")
  
  if [ "$BUILD_NUM" = "null" ] || [ -z "$BUILD_NUM" ]; then
    BUILD_NUM=0
  fi
  
  # Increment and update
  NEW_BUILD_NUM=$((BUILD_NUM + 1))
  jq --arg build "$NEW_BUILD_NUM" '.version.build = ($build | tonumber)' "$URL_JSON_PATH" > "$URL_JSON_PATH.tmp"
  
  if [ $? -eq 0 ]; then
    mv "$URL_JSON_PATH.tmp" "$URL_JSON_PATH"
    echo "Build number updated: $BUILD_NUM -> $NEW_BUILD_NUM"
  else
    echo "Failed to update build number"
    rm -f "$URL_JSON_PATH.tmp"
  fi
fi

echo "Dependencies update completed successfully!"
echo "Updated url.json at: $URL_JSON_PATH"
