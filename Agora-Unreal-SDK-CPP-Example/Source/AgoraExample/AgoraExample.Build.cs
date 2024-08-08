// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using System;
using UnrealBuildTool;

public class AgoraExample : ModuleRules
{
	public AgoraExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "AgoraPlugin", 
            "MediaAssets", 
            "RHI", 
            "HTTP", 
            "AudioMixer",
            //"MyShaderLibrary",

            // For JoinChannelWithToken
            "HTTP",
            "Json",
            "JsonUtilities",


            // For UE5 Compilation
            "AudioExtensions"
        });

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "AndroidPermission" });
            string UPLFilePath = Path.Combine(ModuleDirectory, "UPL","AgoraExample_UPL.xml");
            Console.WriteLine("AgoraExample UPL Path: " + UPLFilePath);
            // Modify AndroidMenifest.xml
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", UPLFilePath);
        }
        //Uncomment if you are using Slate UI

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
