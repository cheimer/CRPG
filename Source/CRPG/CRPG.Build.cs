// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CRPG : ModuleRules
{
	public CRPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore" ,
			"AIModule",
			"NavigationSystem",
			"GamePlayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		PublicIncludePaths.AddRange(new string[] 
		{
			"CRPG/Public/Character",
			"CRPG/Public/Components",
			"CRPG/Public/AI",
			"CRPG/Public/UI",
			"CRPG/Public/AI/Service",
			"CRPG/Public/Menu"
		});
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
