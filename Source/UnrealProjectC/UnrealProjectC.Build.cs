// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealProjectC : ModuleRules
{
	public UnrealProjectC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" ,"HairStrandsCore","Niagara","GeometryCollectionEngine","UMG"});
	}
}
