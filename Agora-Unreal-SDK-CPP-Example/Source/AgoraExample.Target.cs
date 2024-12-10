// Copyright(c) 2024 Agora.io. All rights reserved.

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

            /* ======== It's related to your Xcode Version ====== */


            // [-Wno-unused-but-set-variable]: fix error "variable 'layerNames' set but not used"
            // [-Wno-gcc-compat]: gcc does not allow an attribute in this position on a function declaration
            // [-Wno-reorder-ctor]: fix error "field 'eventHandler' will be initialized after field 'mccUid'"

            // For UE427:
            // [-Wno-deprecated-builtins]: UE_4.27/Engine/Source/Runtime/Core/Public/Templates/IsTriviallyCopyConstructible.h:13:17: error: builtin __has_trivial_copy is deprecated; use __is_trivially_copyable instead
            //  enum { Value = __has_trivial_copy(T) };

            // [-Wno-bitwise-instead-of-logical]: UE_4.27/Engine/Source/Runtime/CoreUObject/Public/AssetRegistry/AssetDataTagMap.h:36:32: note: cast one or both operands to int to silence this warning
            // bool IsEmpty() const { return Class.IsNone() & Package.IsNone() & Object.IsNone(); } //-V792\n

            // [-Wno-single-bit-bitfield-constant-conversion]: UE_4.27/Engine/Source/Runtime/Engine/Public/MaterialShared.h:2304:30: error: implicit truncation from 'int' to a one-bit wide bit-field changes value from 1 to -1 
            //  MarkedForGarbageCollection = 1;
            // AdditionalCompilerArguments = "-Wno-unused-but-set-variable -Wno-gcc-compat -Wno-reorder-ctor -Wno-deprecated-builtins -Wno-bitwise-instead-of-logical -Wno-single-bit-bitfield-constant-conversion";

            // error: unknown warning option '-Wno-deprecated-builtins'; did you mean '-Wno-deprecated-volatile'? [-Werror,-Wunknown-warning-option]
            // error: unknown warning option '-Wno-single-bit-bitfield-constant-conversion'; did you mean '-Wno-bitfield-constant-conversion'? [-Werror,-Wunknown-warning-option]
            AdditionalCompilerArguments = "-Wno-unused-but-set-variable -Wno-gcc-compat -Wno-reorder-ctor";
        }
    }
}
