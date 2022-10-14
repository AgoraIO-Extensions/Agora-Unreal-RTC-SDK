// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AgoraExampleTarget : TargetRules
{
	public AgoraExampleTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			bOverrideBuildEnvironment = true;
			GlobalDefinitions.Add("FORCE_ANSI_ALLOCATOR=1");
		}
		ExtraModuleNames.AddRange( new string[] { "AgoraExample" } );
	}
}
