// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Pillage : ModuleRules
{
	public Pillage(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
