#!/bin/bash
#============================================================================== 
#   download_plugin.sh :  download all the plugins from URLs
#
#    If there is no URL input, the URLs will be set from url_config.txt.
#   
#  $1 SDK Type:
#	 video - download video plugins
#	 audio - download audio plugins
#
#  $3 macOS plugin URL (optional)
#
#  $4 Windows plugin URL (optional)
#
#  $5 iOS plugin URL (optional)
#
#  $6 Android plugin URL (optional)
#
#============================================================================== 


#--------------------------------------
# Set URL
#--------------------------------------
SDK_TYPE=$1
CUR_DIR=$(pwd)
WIN_URL=$2
MAC_URL=$3
ANDROID_URL=$4
IOS_URL=$5

#--------------------------------------
# Set URL
#--------------------------------------

FLAG=0
while read -r line; do
    if [[ $line == *">>>$SDK_TYPE"* ]]; then
        FLAG=1
    fi
    if [[ $line == *"<<<end"* ]]; then
        FLAG=0
    fi

    if [[ $FLAG == 1 ]]; then
        case $line in
            *"IOS"*)
                if [ -z "$5" ]; then
                    IOS_URL=$(echo "$line" | sed 's/IOS[[:space:]]*=//;s/^[[:space:]]*//')
                else
                    IOS_URL=$5
                fi
                ;;
            *"ANDROID"*)
                if [ -z "$4" ]; then
                    ANDROID_URL=$(echo "$line" | sed 's/ANDROID[[:space:]]*=//;s/^[[:space:]]*//')
                else
                    ANDROID_URL=$4
                fi
                ;;
            *"MAC"*)
                if [ -z "$3" ]; then
                    MAC_URL=$(echo "$line" | sed 's/MAC[[:space:]]*=//;s/^[[:space:]]*//')
                else
                    MAC_URL=$3
                fi
                ;;
            *"WIN"*)
                if [ -z "$2" ]; then
                    WIN_URL=$(echo "$line" | sed 's/WIN[[:space:]]*=//;s/^[[:space:]]*//')
                else
                    WIN_URL=$2
                fi
                ;;
        esac
    fi
done < "$CUR_DIR/url_config.txt"


#--------------------------------------
# Download plugins
#--------------------------------------
echo "IOS URL: $IOS_URL"
echo "ANDROID URL: $ANDROID_URL"
echo "MAC URL: $MAC_URL"
echo "WIN URL: $WIN_URL"
HEADER=""
mkdir "$CUR_DIR"/temp/ios "$CUR_DIR"/temp/android "$CUR_DIR"/temp/mac "$CUR_DIR"/temp/win
wget -q --header="$HEADER" "$IOS_URL" -P "$CUR_DIR"/temp/ios
wget -q --header="$HEADER" "$ANDROID_URL" -P "$CUR_DIR"/temp/android
wget -q --header="$HEADER" "$MAC_URL" -P "$CUR_DIR"/temp/mac
wget -q --header="$HEADER" "$WIN_URL" -P "$CUR_DIR"/temp/win 
echo "Download plugins done"

#--------------------------------------
# Extract plugins
#--------------------------------------
unzip -d "$CUR_DIR"/temp/ios/ "$CUR_DIR"/temp/ios/*.zip
unzip -d "$CUR_DIR"/temp/android/ "$CUR_DIR"/temp/android/*.zip
unzip -d "$CUR_DIR"/temp/mac/ "$CUR_DIR"/temp/mac/*.zip
unzip -d "$CUR_DIR"/temp/win/ "$CUR_DIR"/temp/win/*.zip

#--------------------------------------
# Delete zip files
#--------------------------------------
rm "$CUR_DIR"/temp/ios/*.zip "$CUR_DIR"/temp/android/*.zip "$CUR_DIR"/temp/mac/*.zip "$CUR_DIR"/temp/win/*.zip

exit 0
