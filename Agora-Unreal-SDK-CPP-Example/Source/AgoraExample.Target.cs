// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AgoraExampleTarget : TargetRules
{
	public AgoraExampleTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			bOverrideBuildEnvironment = true;
			GlobalDefinitions.Add("FORCE_ANSI_ALLOCATOR=1");
		}
		ExtraModuleNames.AddRange( new string[] { "AgoraExample" } );


        if (Target.Platform == UnrealTargetPlatform.IOS || Target.Platform == UnrealTargetPlatform.Mac)
        {
            bOverrideBuildEnvironment = true;
            // -Wno-unused-but-set-variable£º fix error "variable 'layerNames' set but not used"
            //  -Wno-gcc-compat: gcc does not allow an atrribute in this position on a function declaration
            // -Wno-reorder-ctor: fix error "field 'eventHandler' will be initialized after field 'mccUid'"
            AdditionalCompilerArguments = "-Wno-unused-but-set-variable -Wno-gcc-compat -Wno-reorder-ctor";
        }
    }
}
