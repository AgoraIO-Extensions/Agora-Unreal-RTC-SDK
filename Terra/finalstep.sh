#!/usr/bin/env bash
set -e
set -x
MY_PATH=$(realpath $(dirname "$0"))
PROJECT_ROOT=$(realpath ${MY_PATH})

ls -a packages/cpp
ls -a packages/blueprint
cp ${PROJECT_ROOT}/packages/cpp/AgoraUERtcEngine.h ${PROJECT_ROOT}/../Agora-Unreal-SDK-CPP/AgoraPlugin/Source/AgoraPlugin/Public/AgoraCppPlugin/AgoraUERtcEngine.h
cp ${PROJECT_ROOT}/packages/cpp/AgoraUERtcEngine.cpp ${PROJECT_ROOT}/../Agora-Unreal-SDK-CPP/AgoraPlugin/Source/AgoraPlugin/Private/AgoraCppPlugin/AgoraUERtcEngine.cpp