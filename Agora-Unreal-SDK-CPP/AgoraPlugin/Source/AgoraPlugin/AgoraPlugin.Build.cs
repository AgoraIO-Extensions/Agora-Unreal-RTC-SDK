// C// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AgoraPlugin : ModuleRules
{
	public AgoraPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		// Notice: In current version, the audio only plugin is only for Android / IOS.
        PublicDefinitions.Add("AGORA_UESDK_AUDIO_ONLY=1");

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
	}
}
