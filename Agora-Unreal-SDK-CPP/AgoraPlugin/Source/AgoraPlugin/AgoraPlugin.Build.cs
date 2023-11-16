//  Copyright (c) 2023 Agora.io. All rights reserved.

using System;
using UnrealBuildTool;
using System.Reflection;

public class AgoraPlugin : ModuleRules
{
    public AgoraPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // [Voice (audio-only) / Full]
        // SDK is [Voice] Version or not.
        bool bIsAudioOnlySDK = false;

        // Notice: for now, the audio-only plugin is only available for Android and iOS. The [Windows/Mac] version still remains the FULL version, even if you have downloaded the voice version SDK.
        PublicDefinitions.Add(String.Format("AGORA_UESDK_AUDIO_ONLY={0}", (bIsAudioOnlySDK ? 1 : 0)));

        // Whether to compile video-related code or not.
        if (!bIsAudioOnlySDK || (!(Target.Platform == UnrealTargetPlatform.Android || Target.Platform == UnrealTargetPlatform.IOS)))
        {
            PublicDefinitions.Add("AGORA_UESDK_ENABLE_VIDEO=1");
        }
        else
        {
            PublicDefinitions.Add("AGORA_UESDK_ENABLE_VIDEO=0");
        }

        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
			}
            );

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            //for JNI
            PrivateDependencyModuleNames.AddRange(new string[]
                {
                    "Launch"
                }
            );
        }
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "AgoraPluginLibrary",
                "Projects"
				// ... add other public dependencies that you statically link with here ...
			}
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UMG",
				// ... add private dependencies that you statically link with here ...	
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );
        
        
        // Add Compile Options
        if (Target.Platform == UnrealTargetPlatform.Mac || Target.Platform == UnrealTargetPlatform.IOS)
        {
            Type TargetType = Target.GetType();
            FieldInfo InnerField = TargetType.GetField("Inner",BindingFlags.Instance | BindingFlags.NonPublic);
            TargetRules Inner = (TargetRules) InnerField.GetValue(Target);
            Inner.AdditionalCompilerArguments += " -Wno-gcc-compat -Wno-reorder-ctor -Wno-nonportable-include-path ";
        }
    }
}
