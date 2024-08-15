// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomMutipleScreen.h"

#define LOCTEXT_NAMESPACE "FCustomMutipleScreenModule"

void FCustomMutipleScreenModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FCustomMutipleScreenModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomMutipleScreenModule, CustomMutipleScreen)