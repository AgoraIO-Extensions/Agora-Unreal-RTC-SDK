##################################
# --- Guidelines: ---
#
# Common Environment Variable:
# 'Package_Publish:boolean:true',
# 'Clean_Clone:boolean:false',
# 'is_tag_fetch:boolean:false',
# 'is_offical_build:boolean:false',
# 'repo:string',
# 'base:string',
# 'arch:string'
# 'output:string'
# 'short_version:string'
# 'release_version:string'
# 'build_date:string(yyyyMMdd)',
# 'build_timestamp:string (yyyyMMdd_hhmm)',
# 'platform: string',
# 'BUILD_NUMBER: string',
# 'WORKSPACE: string'
#
# --- Test Related: ---
#   PR build, zip test related to test.zip
#   Package build, zip package related to package.zip
# --- Artifactory Related: ---
# download artifactory:
# python3 ${WORKSPACE}/artifactory_utils.py --action=download_file --file=ARTIFACTORY_URL
# upload file to artifactory:
# python3 ${WORKSPACE}/artifactory_utils.py --action=upload_file --file=FILEPATTERN --server_path=SERVERPATH --server_repo=SERVER_REPO --with_pattern
# for example: python3 ${WORKSPACE}/artifactory_utils.py --action=upload_file --file=*.zip --server_path=windows/ --server_repo=ACCS_repo --with_pattern
# upload folder to artifactory
# python3 ${WORKSPACE}/artifactory_utils.py --action=upload_file --file=FILEPATTERN --server_path=SERVERPATH --server_repo=SERVER_REPO --with_folder
# for example: python3 ${WORKSPACE}/artifactory_utils.py --action=upload_file --file=*.zip --server_path=windows/ --server_repo=ACCS_repo --with_folder
# --- Input: ----
# sourcePath: see jenkins console for details.
# WORKSPACE: ${WORKSPACE}
# --- Output: ----
# pr: output test.zip to workspace dir
# others: Rename the zip package name yourself, But need copy it to workspace dir
##################################

echo Package_Publish: $Package_Publish
echo is_tag_fetch: $is_tag_fetch
echo arch: $arch
echo source_root: %source_root%
echo output: /tmp/jenkins/${project}_out
echo build_date: $build_date
echo build_time: $build_time
echo release_version: $release_version
echo short_version: $short_version
echo pwd: `pwd`

#--------------------------------------
# Prepare all the required resources
#--------------------------------------
ROOT_DIR=$(pwd)/Agora-Unreal-SDK-CPP
CI_DIR=$(pwd)/Agora-Unreal-SDK-CPP/CI
Template_DIR=$(pwd)/Agora-Unreal-SDK-CPP/AgoraPlugin
PLUGIN_NAME="AgoraPlugin"

#echo "[Unreal CI] start preparing resources"
cd "$CI_DIR" || exit 1
mkdir temp
sh ./download_plugin.sh "$SDK_TYPE" "$url_windows" "$url_mac" "$url_android" "$url_ios"
ANDROID_SRC_PATH="$CI_DIR"/temp/android/
IOS_SRC_PATH="$CI_DIR"/temp/ios/
MAC_SRC_PATH="$CI_DIR"/temp/mac/
WIN_SRC_PATH="$CI_DIR"/temp/win/
cd temp || exit 1
#git clone -b "$BRANCH" git@github.com:oneSitDown/agora-plugin.git
cd "$CI_DIR" || exit 1
echo "[Unreal CI] finish preparing resources"


#--------------------------------------
# Copy files to the Unity project
#--------------------------------------
echo "[Unreal CI] start copying files"
cp -r $Template_DIR $CI_DIR/temp
PLUGIN_PATH=$CI_DIR/temp/"$PLUGIN_NAME"/Source/ThirdParty/"$PLUGIN_NAME"Library

echo "[Unreal CI] copying Android ..."
ANDROID_DST_PATH="$PLUGIN_PATH"/Android/Release
mkdir -p $ANDROID_DST_PATH
rm -f ANDROID_DST_PATH/*
cp -r "$ANDROID_SRC_PATH"/Agora_*/rtc/sdk/ "$ANDROID_DST_PATH"

if [ "$profile" == "FULL" ]; then
    rm -rf "$PLUGIN_PATH"/Android/Release/APL_armv7TemplateVoice.xml
    mv "$PLUGIN_PATH"/Android/Release/APL_armv7TemplateFULL.xml "$PLUGIN_PATH"/Android/Release/APL_armv7Template.xml
elif [ "$profile" == "VOICE" ]; then
    rm -rf "$PLUGIN_PATH"/Android/Release/APL_armv7TemplateFULL.xml
    mv "$PLUGIN_PATH"/Android/Release/APL_armv7TemplateVOICE.xml "$PLUGIN_PATH"/Android/Release/APL_armv7Template.xml
fi

echo "[Unreal CI] copying IOS ..."
IOS_DST_PATH="$PLUGIN_PATH/IOS/Release"
mkdir -p $IOS_DST_PATH
rm -f IOS_DST_PATH/*
cp -PRf $IOS_SRC_PATH/Agora_*/libs/*.xcframework/ios-arm64_armv7/*framework "$IOS_DST_PATH"

echo "[Unreal CI] Zip IOS Framework..."
cd $IOS_DST_PATH
list=`ls -1`
for var in $list
do
zip -r $var.zip $var
done
rm -r *.framework
cd "$CI_DIR"

echo "[Unreal CI] copying Mac ..."
MAC_DST_PATH="$PLUGIN_PATH/Mac/Release"
mkdir -p $MAC_DST_PATH
rm -f MAC_DST_PATH/*
cp -PRf $MAC_SRC_PATH/Agora_*/libs/*.xcframework/macos-arm64_x86_64/*framework "$MAC_DST_PATH"

echo "[Unreal CI] copying Win x86 ..."
WINx86_DST_PATH="$PLUGIN_PATH/Win/Release/"
mkdir -p $WINx86_DST_PATH
rm -f WINx86_DST_PATH/*
cp -PRf $WIN_SRC_PATH/Agora_*/sdk/x86 "$WINx86_DST_PATH"

echo "[Unreal CI] copying Win x86_64 ..."
WINx86_64_DST_PATH="$PLUGIN_PATH/Win/Release/"
mkdir -p $WINx86_64_DST_PATH
rm -f WINx86_64_DST_PATH/*
cp -PRf $WIN_SRC_PATH/Agora_*/sdk/x86_64 "$WINx86_64_DST_PATH"

cd $CI_DIR/temp

#--------------------------------------
# Zip Package
#--------------------------------------

zip -r "$PLUGIN_NAME".zip $PLUGIN_NAME

#--------------------------------------
# Copy to $CI_DIR/output
#--------------------------------------

mkdir "$CI_DIR"/output

mv "$CI_DIR"/temp/"$PLUGIN_NAME".zip  "$CI_DIR"/temp/Agora_Unreal_RTC_${SDK_TYPE}_SDK_${SDK_VERSION}_${profile}_${build_time}_${BUILD_NUMBER}.zip

cp "$CI_DIR"/temp/Agora_Unreal_RTC_${SDK_TYPE}_SDK_${SDK_VERSION}_${profile}_${build_time}_${BUILD_NUMBER}.zip "$WORKSPACE" || exit 1

rm -rf "$CI_DIR"/temp

exit 0;