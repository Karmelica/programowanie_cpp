// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CppPrograming : ModuleRules
{
	public CppPrograming(ReadOnlyTargetRules Target) : base(Target)
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
			"CppPrograming",
			"CppPrograming/Variant_Platforming",
			"CppPrograming/Variant_Combat",
			"CppPrograming/Variant_Combat/AI",
			"CppPrograming/Variant_SideScrolling",
			"CppPrograming/Variant_SideScrolling/Gameplay",
			"CppPrograming/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
