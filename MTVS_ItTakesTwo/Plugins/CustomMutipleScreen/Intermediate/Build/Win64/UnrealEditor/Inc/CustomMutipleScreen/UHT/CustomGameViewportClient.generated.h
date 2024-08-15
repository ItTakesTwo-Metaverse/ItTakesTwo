// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CustomGameViewportClient.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef CUSTOMMUTIPLESCREEN_CustomGameViewportClient_generated_h
#error "CustomGameViewportClient.generated.h already included, missing '#pragma once' in CustomGameViewportClient.h"
#endif
#define CUSTOMMUTIPLESCREEN_CustomGameViewportClient_generated_h

#define FID_Projects_Unreal_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_47_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execUpdateLayoutWithNewRatio);


#define FID_Projects_Unreal_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_47_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCustomGameViewportClient(); \
	friend struct Z_Construct_UClass_UCustomGameViewportClient_Statics; \
public: \
	DECLARE_CLASS(UCustomGameViewportClient, UGameViewportClient, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/CustomMutipleScreen"), NO_API) \
	DECLARE_SERIALIZER(UCustomGameViewportClient)


#define FID_Projects_Unreal_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_47_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UCustomGameViewportClient(UCustomGameViewportClient&&); \
	UCustomGameViewportClient(const UCustomGameViewportClient&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCustomGameViewportClient); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCustomGameViewportClient); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UCustomGameViewportClient) \
	NO_API virtual ~UCustomGameViewportClient();


#define FID_Projects_Unreal_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_44_PROLOG
#define FID_Projects_Unreal_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_47_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_Unreal_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_47_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Projects_Unreal_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_47_INCLASS_NO_PURE_DECLS \
	FID_Projects_Unreal_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_47_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CUSTOMMUTIPLESCREEN_API UClass* StaticClass<class UCustomGameViewportClient>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_Unreal_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h


#define FOREACH_ENUM_ECUSTOMSPLITSCREENTYPE(op) \
	op(ECustomSplitScreenType::None) \
	op(ECustomSplitScreenType::ThreePlayer) \
	op(ECustomSplitScreenType::OneAndOneValance) \
	op(ECustomSplitScreenType::OneAndTwoValance) \
	op(ECustomSplitScreenType::TwoAndOneValance) \
	op(ECustomSplitScreenType::SplitTypeCount) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
