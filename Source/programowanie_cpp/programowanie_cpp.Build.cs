// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class programowanie_cpp : ModuleRules
{
	public programowanie_cpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"programowanie_cpp",
			"programowanie_cpp/Variant_Platforming",
			"programowanie_cpp/Variant_Combat",
			"programowanie_cpp/Variant_Combat/AI",
			"programowanie_cpp/Variant_SideScrolling",
			"programowanie_cpp/Variant_SideScrolling/Gameplay",
			"programowanie_cpp/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
