// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UCCH03P01 : ModuleRules
{
	public UCCH03P01(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
