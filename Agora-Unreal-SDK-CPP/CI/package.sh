#!/bin/bash
#============================================================================== 
#   package.sh :  pack Agora Unreal RTC SDK into a Unreal package
#
#  $1 SDK_TYPE
#
#  $2 The branch name of API-Example
#
#  $3 url_windows (optional)
# 
#  $4 url_mac (optional)
#
#  $5 url_android (optional)
#
#  $6 url_ios (optional)
#
#============================================================================== 


set -ex

#--------------------------------------
# Prepare all the required resources
#--------------------------------------
ROOT_DIR=$(pwd)/Agora-Unreal-SDK-CPP
CI_DIR=$(pwd)/Agora-Unreal-SDK-CPP/CI
Template_DIR=$(pwd)/Agora-Unreal-SDK-CPP/AgoraPlugin
PLUGIN_NAME="AgoraPlugin"
SDK_TYPE=$1
DEMO_BRANCH=$2

git checkout DEMO_BRANCH
#echo "[Unreal CI] start preparing resources"
cd "$CI_DIR" || exit 1
mkdir temp
sh ./download_plugin.sh "$SDK_TYPE" "$3" "$4" "$5" "$6"
ANDROID_SRC_PATH="$CI_DIR"/temp/android/
IOS_SRC_PATH=$CI_DIR/temp/ios/
MAC_SRC_PATH="$CI_DIR"/temp/mac/
WIN_SRC_PATH="$CI_DIR"/temp/win/
cd temp || exit 1
#git clone -b "$DEMO_BRANCH" git@github.com:oneSitDown/agora-plugin.git
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

if [ "$SDK_TYPE" == "FULL" ]; then
    rm -rf "$PLUGIN_PATH"/Android/Release/APL_armv7TemplateVoice.xml
    mv "$PLUGIN_PATH"/Android/Release/APL_armv7TemplateFULL.xml "$PLUGIN_PATH"/Android/Release/APL_armv7Template.xml
elif [ "$SDK_TYPE" == "Voice" ]; then
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
cp "$CI_DIR"/temp/"$PLUGIN_NAME".zip "$CI_DIR"/output || exit 1

rm -rf "$CI_DIR"/temp

exit 0;



