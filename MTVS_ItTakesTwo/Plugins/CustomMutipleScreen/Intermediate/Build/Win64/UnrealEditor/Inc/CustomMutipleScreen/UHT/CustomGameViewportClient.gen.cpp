// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CustomMutipleScreen/Public/CustomGameViewportClient.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCustomGameViewportClient() {}

// Begin Cross Module References
CUSTOMMUTIPLESCREEN_API UClass* Z_Construct_UClass_UCustomGameViewportClient();
CUSTOMMUTIPLESCREEN_API UClass* Z_Construct_UClass_UCustomGameViewportClient_NoRegister();
CUSTOMMUTIPLESCREEN_API UEnum* Z_Construct_UEnum_CustomMutipleScreen_ECustomSplitScreenType();
ENGINE_API UClass* Z_Construct_UClass_UGameViewportClient();
UPackage* Z_Construct_UPackage__Script_CustomMutipleScreen();
// End Cross Module References

// Begin Enum ECustomSplitScreenType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECustomSplitScreenType;
static UEnum* ECustomSplitScreenType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ECustomSplitScreenType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ECustomSplitScreenType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CustomMutipleScreen_ECustomSplitScreenType, (UObject*)Z_Construct_UPackage__Script_CustomMutipleScreen(), TEXT("ECustomSplitScreenType"));
	}
	return Z_Registration_Info_UEnum_ECustomSplitScreenType.OuterSingleton;
}
template<> CUSTOMMUTIPLESCREEN_API UEnum* StaticEnum<ECustomSplitScreenType::Type>()
{
	return ECustomSplitScreenType_StaticEnum();
}
struct Z_Construct_UEnum_CustomMutipleScreen_ECustomSplitScreenType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/CustomGameViewportClient.h" },
		{ "None.Comment", "// 0 value required by UE\n" },
		{ "None.Name", "ECustomSplitScreenType::None" },
		{ "None.ToolTip", "0 value required by UE" },
		{ "OneAndOneValance.Name", "ECustomSplitScreenType::OneAndOneValance" },
		{ "OneAndTwoValance.Name", "ECustomSplitScreenType::OneAndTwoValance" },
		{ "SplitTypeCount.Name", "ECustomSplitScreenType::SplitTypeCount" },
		{ "ThreePlayer.Comment", "// Custom Splitscreen, next value after last built-in splitscreen type\n" },
		{ "ThreePlayer.Name", "ECustomSplitScreenType::ThreePlayer" },
		{ "ThreePlayer.ToolTip", "Custom Splitscreen, next value after last built-in splitscreen type" },
		{ "TwoAndOneValance.Name", "ECustomSplitScreenType::TwoAndOneValance" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ECustomSplitScreenType::None", (int64)ECustomSplitScreenType::None },
		{ "ECustomSplitScreenType::ThreePlayer", (int64)ECustomSplitScreenType::ThreePlayer },
		{ "ECustomSplitScreenType::OneAndOneValance", (int64)ECustomSplitScreenType::OneAndOneValance },
		{ "ECustomSplitScreenType::OneAndTwoValance", (int64)ECustomSplitScreenType::OneAndTwoValance },
		{ "ECustomSplitScreenType::TwoAndOneValance", (int64)ECustomSplitScreenType::TwoAndOneValance },
		{ "ECustomSplitScreenType::SplitTypeCount", (int64)ECustomSplitScreenType::SplitTypeCount },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CustomMutipleScreen_ECustomSplitScreenType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_CustomMutipleScreen,
	nullptr,
	"ECustomSplitScreenType",
	"ECustomSplitScreenType::Type",
	Z_Construct_UEnum_CustomMutipleScreen_ECustomSplitScreenType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_CustomMutipleScreen_ECustomSplitScreenType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::Namespaced,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_CustomMutipleScreen_ECustomSplitScreenType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_CustomMutipleScreen_ECustomSplitScreenType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_CustomMutipleScreen_ECustomSplitScreenType()
{
	if (!Z_Registration_Info_UEnum_ECustomSplitScreenType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECustomSplitScreenType.InnerSingleton, Z_Construct_UEnum_CustomMutipleScreen_ECustomSplitScreenType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ECustomSplitScreenType.InnerSingleton;
}
// End Enum ECustomSplitScreenType

// Begin Class UCustomGameViewportClient Function UpdateLayoutWithNewRatio
struct Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics
{
	struct CustomGameViewportClient_eventUpdateLayoutWithNewRatio_Parms
	{
		float a;
		float b;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/CustomGameViewportClient.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_a;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_b;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::NewProp_a = { "a", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CustomGameViewportClient_eventUpdateLayoutWithNewRatio_Parms, a), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::NewProp_b = { "b", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CustomGameViewportClient_eventUpdateLayoutWithNewRatio_Parms, b), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::NewProp_a,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::NewProp_b,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCustomGameViewportClient, nullptr, "UpdateLayoutWithNewRatio", nullptr, nullptr, Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::CustomGameViewportClient_eventUpdateLayoutWithNewRatio_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::CustomGameViewportClient_eventUpdateLayoutWithNewRatio_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCustomGameViewportClient::execUpdateLayoutWithNewRatio)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_a);
	P_GET_PROPERTY(FFloatProperty,Z_Param_b);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateLayoutWithNewRatio(Z_Param_a,Z_Param_b);
	P_NATIVE_END;
}
// End Class UCustomGameViewportClient Function UpdateLayoutWithNewRatio

// Begin Class UCustomGameViewportClient
void UCustomGameViewportClient::StaticRegisterNativesUCustomGameViewportClient()
{
	UClass* Class = UCustomGameViewportClient::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "UpdateLayoutWithNewRatio", &UCustomGameViewportClient::execUpdateLayoutWithNewRatio },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCustomGameViewportClient);
UClass* Z_Construct_UClass_UCustomGameViewportClient_NoRegister()
{
	return UCustomGameViewportClient::StaticClass();
}
struct Z_Construct_UClass_UCustomGameViewportClient_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "CustomGameViewportClient.h" },
		{ "ModuleRelativePath", "Public/CustomGameViewportClient.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewRatio_MetaData[] = {
		{ "Category", "CustomGameViewportClient" },
		{ "ModuleRelativePath", "Public/CustomGameViewportClient.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MayView_MetaData[] = {
		{ "Category", "CustomGameViewportClient" },
		{ "ModuleRelativePath", "Public/CustomGameViewportClient.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CodyView_MetaData[] = {
		{ "Category", "CustomGameViewportClient" },
		{ "ModuleRelativePath", "Public/CustomGameViewportClient.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewRatio;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MayView;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CodyView;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCustomGameViewportClient_UpdateLayoutWithNewRatio, "UpdateLayoutWithNewRatio" }, // 2733657849
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCustomGameViewportClient>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomGameViewportClient_Statics::NewProp_NewRatio = { "NewRatio", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomGameViewportClient, NewRatio), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewRatio_MetaData), NewProp_NewRatio_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomGameViewportClient_Statics::NewProp_MayView = { "MayView", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomGameViewportClient, MayView), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MayView_MetaData), NewProp_MayView_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomGameViewportClient_Statics::NewProp_CodyView = { "CodyView", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomGameViewportClient, CodyView), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CodyView_MetaData), NewProp_CodyView_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCustomGameViewportClient_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomGameViewportClient_Statics::NewProp_NewRatio,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomGameViewportClient_Statics::NewProp_MayView,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomGameViewportClient_Statics::NewProp_CodyView,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomGameViewportClient_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UCustomGameViewportClient_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameViewportClient,
	(UObject* (*)())Z_Construct_UPackage__Script_CustomMutipleScreen,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomGameViewportClient_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCustomGameViewportClient_Statics::ClassParams = {
	&UCustomGameViewportClient::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UCustomGameViewportClient_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UCustomGameViewportClient_Statics::PropPointers),
	0,
	0x001000ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomGameViewportClient_Statics::Class_MetaDataParams), Z_Construct_UClass_UCustomGameViewportClient_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCustomGameViewportClient()
{
	if (!Z_Registration_Info_UClass_UCustomGameViewportClient.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCustomGameViewportClient.OuterSingleton, Z_Construct_UClass_UCustomGameViewportClient_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCustomGameViewportClient.OuterSingleton;
}
template<> CUSTOMMUTIPLESCREEN_API UClass* StaticClass<UCustomGameViewportClient>()
{
	return UCustomGameViewportClient::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCustomGameViewportClient);
UCustomGameViewportClient::~UCustomGameViewportClient() {}
// End Class UCustomGameViewportClient

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Admin_Documents_challage_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ECustomSplitScreenType_StaticEnum, TEXT("ECustomSplitScreenType"), &Z_Registration_Info_UEnum_ECustomSplitScreenType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 183197005U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCustomGameViewportClient, UCustomGameViewportClient::StaticClass, TEXT("UCustomGameViewportClient"), &Z_Registration_Info_UClass_UCustomGameViewportClient, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCustomGameViewportClient), 1901390995U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Admin_Documents_challage_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_203973196(TEXT("/Script/CustomMutipleScreen"),
	Z_CompiledInDeferFile_FID_Users_Admin_Documents_challage_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Admin_Documents_challage_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_Admin_Documents_challage_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Admin_Documents_challage_ItTakesTwo_MTVS_ItTakesTwo_Plugins_CustomMutipleScreen_Source_CustomMutipleScreen_Public_CustomGameViewportClient_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
