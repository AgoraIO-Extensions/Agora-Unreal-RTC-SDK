// Copyright(c) 2024 Agora.io. All rights reserved.

using System;
using System.Linq;
using System.IO;
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


        // if need to set callbacks during agora sdk lifetime
        bool bWithAgoraCallbacks = true;
        PublicDefinitions.Add(String.Format("WITH_AGORA_CALLBACKS={0}", (bWithAgoraCallbacks ? 1 : 0)));

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
                Path.Combine(ModuleDirectory,"Public","AgoraCppPlugin"),
                Path.Combine(ModuleDirectory,"Public","AgoraCppPlugin","include"),
                // "AgoraPlugin/Public/AgoraCppPlugin/include",
                 Path.Combine(ModuleDirectory,"Public","AgoraBlueprintPlugin"),
            }
            );


        bool bUseBlueprintModule = true;

        if(bUseBlueprintModule)
        {
            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "MediaAssets",
                    "AgoraUtilityHelper",
                }
            );
        }


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
                Path.Combine(ModuleDirectory,"Private","AgoraCppPlugin","PrivateInclude"),
                Path.Combine(ModuleDirectory,"Private","AgoraCppPlugin","PrivateInclude","VideoRender"),
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
                "Projects",
                "AgoraPluginLibrary",

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



        /* ==== For Test Build Plugin === 
           AdditionalCompilerArguments are only required on the Mac or iOS platforms.
         */


        //// Add Compile Options
        //if (Target.Platform == UnrealTargetPlatform.Mac || Target.Platform == UnrealTargetPlatform.IOS)
        //{
        //    // -Wno-gcc-compat: gcc does not allow an atrribute in this position on a function declaration
        //    // -Wno-reorder-ctor: fix error "field 'eventHandler' will be initialized after field 'mccUid'"
        //    // -Wno-nonportable-include-path: In some cases, path <Private\AgoraCppPlugin\Include> would be changed from <Include> to <include>.
        //    Type TargetType = Target.GetType();
        //    FieldInfo InnerField = TargetType.GetField("Inner", BindingFlags.Instance | BindingFlags.NonPublic);
        //    TargetRules Inner = (TargetRules)InnerField.GetValue(Target);
        //    Inner.AdditionalCompilerArguments += " -Wno-gcc-compat -Wno-reorder-ctor -Wno-nonportable-include-path -Wno-undef  -Wno-macro-redefined ";


        /*
            //// If UE4.27 or lower than 4.27 fails
            // Inner.AdditionalCompilerArguments += " -Wno-deprecated-builtins -Wno-unused-but-set-variable -Wno-single-bit-bitfield-constant-conversion -Wno-bitwise-instead-of-logical ";
         */


        //}



        if (Target.GlobalDefinitions.Contains("FORCE_ANSI_ALLOCATOR=1"))
        {

            PublicDefinitions.Add(string.Format("USE_ANSI_ALLOCATOR=1"));
            Console.WriteLine("[Agora Allocator] Use ANSI Allocator");

            PublicDependencyModuleNames.AddRange(new string[] { "Eigen" });
        }
        else
        {
            PublicDefinitions.Add(string.Format("USE_ANSI_ALLOCATOR=0"));
            Console.WriteLine("[Agora Allocator] Use UE Allocator");
        }
    }
}
