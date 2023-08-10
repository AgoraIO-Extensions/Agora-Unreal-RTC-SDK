// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using System;
using UnrealBuildTool;

public class AgoraBPExample : ModuleRules
{
	public AgoraBPExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true


        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "AndroidPermission" });
            string UPLFilePath = Path.Combine(ModuleDirectory, "UPL", "AgoraExample_UPL.xml");
            Console.WriteLine("AgoraExample UPL Path: " + UPLFilePath);
            // Modify AndroidMenifest.xml
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", UPLFilePath);
        }
    }
}
