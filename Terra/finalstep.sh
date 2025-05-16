#!/usr/bin/env bash
set -e
set -x
MY_PATH=$(realpath $(dirname "$0"))
PROJECT_ROOT=$(realpath ${MY_PATH})

ls -a packages/cpp
ls -a packages/blueprint

# TBD(WinterPu): change file name to AgoraUERTCEngine.h and AgoraUERTCEngine.cpp
cp ${PROJECT_ROOT}/packages/cpp/AgoraUERtcEngine.h ${PROJECT_ROOT}/../Agora-Unreal-SDK-CPP/AgoraPlugin/Source/AgoraPlugin/Public/AgoraCppPlugin/AgoraUERTCEngine.h
cp ${PROJECT_ROOT}/packages/cpp/AgoraUERtcEngine.cpp ${PROJECT_ROOT}/../Agora-Unreal-SDK-CPP/AgoraPlugin/Source/AgoraPlugin/Private/AgoraCppPlugin/AgoraUERTCEngine.cpp