// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "Engine/ViewportSplitScreen.h"
#include "CustomGameViewportClient.generated.h"

UENUM(BlueprintType)
namespace ECustomSplitScreenType
{
     enum Type
     {
          // 0 value required by UE
          None,
          // Custom Splitscreen, next value after last built-in splitscreen type
          ThreePlayer = ESplitScreenType::SplitTypeCount,
          OneAndOneValance,
          OneAndTwoValance,
          TwoAndOneValance,
          SplitTypeCount,
     };
}

#pragma region 
// gpt 개선안
//UENUM ( BlueprintType )
//enum class ECustomSplitScreenType : uint8
//{
//	None UMETA ( DisplayName = "None" ) = 0,
//	OneAndOneValance UMETA ( DisplayName = "1/2 vs 1/2" ) = 11 ,
//	OneAndTwoValance UMETA ( DisplayName = "1/3 vs 2/3" ) = 12 ,
//	TwoAndOneValance UMETA ( DisplayName = "2/3 vs 1/3" ) = 13 ,
//	ThreePlayer UMETA ( DisplayName = "Three Player" ) = 14 ,
//	SplitTypeCount UMETA ( DisplayName = "Split Type Count" ) = 15,
//};
#pragma endregion hold

/**
 * 
 */

UCLASS()
class CUSTOMMUTIPLESCREEN_API UCustomGameViewportClient : public UGameViewportClient
{
    GENERATED_BODY ( )

public:
    UCustomGameViewportClient ( );

    virtual void UpdateActiveSplitscreenType ( ) override;

#pragma region 
    //void SmoothTransitionToLayout ( float TargetRatio , float Duration );

    //void AdjustSplitScreenStep ( );
    
    //UFUNCTION(BlueprintCallable, Category = "Screen")
    //void StartAdjustingSplitScreen(float StartRatio, float TargetRatio, float Duration);
#pragma endregion hold

    UFUNCTION(BlueprintCallable )
    void UpdateLayoutWithNewRatio ( float a, float b );

    UPROPERTY(EditAnywhere, BlueprintReadWrite )
    float NewRatio = 0.5f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite )
    float MayView = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite )
    float CodyView = 0.5f;
};
