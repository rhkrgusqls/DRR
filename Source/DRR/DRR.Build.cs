// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DRR : ModuleRules
{
	public DRR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "NavigationSystem", "AIModule", "GameplayTasks", "OnlineSubsystem", "Utilities" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        PublicIncludePaths.AddRange(new string[] { "DRR" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
