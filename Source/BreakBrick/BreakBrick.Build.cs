// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BreakBrick : ModuleRules
{
	public BreakBrick(ReadOnlyTargetRules Target) : base(Target)
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
			"UMG",
			"Slate",
			"DeveloperSettings"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"BreakBrick",
			"BreakBrick/Variant_Platforming",
			"BreakBrick/Variant_Platforming/Animation",
			"BreakBrick/Variant_Combat",
			"BreakBrick/Variant_Combat/AI",
			"BreakBrick/Variant_Combat/Animation",
			"BreakBrick/Variant_Combat/Gameplay",
			"BreakBrick/Variant_Combat/Interfaces",
			"BreakBrick/Variant_Combat/UI",
			"BreakBrick/Variant_SideScrolling",
			"BreakBrick/Variant_SideScrolling/AI",
			"BreakBrick/Variant_SideScrolling/Gameplay",
			"BreakBrick/Variant_SideScrolling/Interfaces",
			"BreakBrick/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
