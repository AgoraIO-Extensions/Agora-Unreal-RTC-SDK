#!/usr/bin/env bash
set -e
set -x
MY_PATH=$(realpath $(dirname "$0"))
PROJECT_ROOT=$(realpath ${MY_PATH})

cp ${PROJECT_ROOT}/packages/cpp/AgoraUERTCEngine.h ${PROJECT_ROOT}/../Agora-Unreal-SDK-CPP/AgoraPlugin/Source/AgoraPlugin/Public/AgoraCppPlugin/AgoraUERTCEngine.h
cp ${PROJECT_ROOT}/packages/cpp/AgoraUERTCEngine.cpp ${PROJECT_ROOT}/../Agora-Unreal-SDK-CPP/AgoraPlugin/Source/AgoraPlugin/Private/AgoraCppPlugin/AgoraUERTCEngine.cpp