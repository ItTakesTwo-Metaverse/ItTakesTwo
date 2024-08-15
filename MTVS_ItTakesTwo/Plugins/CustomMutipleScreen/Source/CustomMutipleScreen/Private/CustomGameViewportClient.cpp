// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameViewportClient.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "TimerManager.h"

#pragma region 
 //기존코드
//UCustomGameViewportClient::UCustomGameViewportClient ( )
//    : Super ( FObjectInitializer::Get ( ) )
//{
//    // Resize SplitscreenInfo to fit our custom config
//    SplitscreenInfo.SetNum ( ECustomSplitScreenType::SplitTypeCount , false );
//
//    // Fill the custom config
//    SplitscreenInfo[ECustomSplitScreenType::ThreePlayer].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.50f , 1.00f , 0.00f , 0.00f ) ); //1
//    SplitscreenInfo[ECustomSplitScreenType::ThreePlayer].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.50f , 1.00f , 0.50f , 0.00f ) ); //2
//    //SplitscreenInfo[ECustomSplitScreenType::ThreePlayer].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.66f , 0.50f , 0.00f , 0.50f ) ); //3
//}

//#pragma region MyRegion
//// gpt 개선안 
//// CustomGameViewportClient.cpp
////UCustomGameViewportClient::UCustomGameViewportClient ( )
////    : Super ( FObjectInitializer::Get ( ) )
////{
////    // Resize SplitscreenInfo to fit our custom config
////    SplitscreenInfo.SetNum ( static_cast<int32>(ECustomSplitScreenType::SplitTypeCount) , false );
////
////    // 1/2 vs 1/2 레이아웃
////    SplitscreenInfo[static_cast<int32>(ECustomSplitScreenType::OneAndOneValance)].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.50f , 1.00f , 0.00f , 0.00f ) ); // Player 1
////    SplitscreenInfo[static_cast<int32>(ECustomSplitScreenType::OneAndOneValance)].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.50f , 1.00f , 0.50f , 0.00f ) ); // Player 2
////
////    // 1/3 vs 2/3 레이아웃
////    SplitscreenInfo[static_cast<int32>(ECustomSplitScreenType::OneAndTwoValance)].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.33f , 1.00f , 0.00f , 0.00f ) ); // Player 1
////    SplitscreenInfo[static_cast<int32>(ECustomSplitScreenType::OneAndTwoValance)].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.67f , 1.00f , 0.33f , 0.00f ) ); // Player 2
////
////    // 2/3 vs 1/3 레이아웃
////    SplitscreenInfo[static_cast<int32>(ECustomSplitScreenType::TwoAndOneValance)].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.67f , 1.00f , 0.00f , 0.00f ) ); // Player 1
////    SplitscreenInfo[static_cast<int32>(ECustomSplitScreenType::TwoAndOneValance)].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.33f , 1.00f , 0.67f , 0.00f ) ); // Player 2
////}
//#pragma endregion worng gpt
//
//UCustomGameViewportClient::UCustomGameViewportClient ( )
//    : Super ( FObjectInitializer::Get ( ) )
//{
//    // Resize SplitscreenInfo to fit our custom config
//    SplitscreenInfo.SetNum ( static_cast<int32>(ECustomSplitScreenType::SplitTypeCount) , false );
//
//    // 1/2 vs 1/2 레이아웃
//    SplitscreenInfo[ECustomSplitScreenType::OneAndOneValance].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.50f , 1.00f , 0.00f , 0.00f ) ); // Player 1
//	SplitscreenInfo[ECustomSplitScreenType::OneAndOneValance].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.50f , 1.00f , 0.50f , 0.00f ) ); // Player 2
//
//    // 1/3 vs 2/3 레이아웃
//    SplitscreenInfo[ECustomSplitScreenType::OneAndTwoValance].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.33f , 1.00f , 0.00f , 0.00f ) ); // Player 1
//    SplitscreenInfo[ECustomSplitScreenType::OneAndTwoValance].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.67f , 1.00f , 0.33f , 0.00f ) ); // Player 2
//
//    // 2/3 vs 1/3 레이아웃
//    SplitscreenInfo[ECustomSplitScreenType::TwoAndOneValance].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.67f , 1.00f , 0.00f , 0.00f ) ); // Player 1
//    SplitscreenInfo[ECustomSplitScreenType::TwoAndOneValance].PlayerData.Add ( FPerPlayerSplitscreenData ( 0.33f , 1.00f , 0.67f , 0.00f ) ); // Player 2
//}
//
//
//void UCustomGameViewportClient::SmoothTransitionToLayout ( float TargetRatio , float Duration )
//{
//    // 예: Lerp를 사용하여 비율을 스무스하게 전환
//    FTimerHandle TimerHandle;
//    float StartRatio = /* 현재 비율 */;
//    float ElapsedTime = 0.0f;
//
//    this->GetWorld ( )->GetTimerManager ( ).SetTimer ( TimerHandle , [this , StartRatio , TargetRatio , ElapsedTime , Duration]( ) mutable {
//        ElapsedTime += GetWorld ( )->GetDeltaSeconds ( );
//        float Alpha = FMath::Clamp ( ElapsedTime / Duration , 0.0f , 1.0f );
//        float NewRatio = FMath::Lerp ( StartRatio , TargetRatio , Alpha );
//
//        // NewRatio를 사용하여 화면 비율 업데이트
//        UpdateLayoutWithNewRatio ( NewRatio );
//
//        if ( Alpha >= 1.0f )
//        {
//            GetWorld ( )->GetTimerManager ( ).ClearTimer ( TimerHandle );
//        }
//    } , GetWorld ( )->GetDeltaSeconds ( ) , true );
//}
//
//
//void UCustomGameViewportClient::UpdateActiveSplitscreenType ( )
//{
//    const int32 NumPlayers = GEngine->GetNumGamePlayers ( GetWorld ( ) );
//
//    if (  )
//
//    if ( NumPlayers == 2 )
//    {
//        // 특정 조건에 따라 레이아웃 선택 (예: 1/2 vs 1/2)
//        // 기존 코드
//        //ActiveSplitscreenType = static_cast<ESplitScreenType::Type>(ECustomSplitScreenType::ThreePlayer);
//        // gpt 개선안
//        ActiveSplitscreenType = static_cast<ESplitScreenType::Type>(ECustomSplitScreenType::OneAndOneValance);
//
//    }
//    else
//    {
//        // 기본 처리
//        Super::UpdateActiveSplitscreenType ( );
//    }
//}

#pragma endregion hold


UCustomGameViewportClient::UCustomGameViewportClient ( ) : Super ( FObjectInitializer::Get ( ) )
{
    SplitscreenInfo.SetNum ( static_cast<int32>(ECustomSplitScreenType::SplitTypeCount) , false );

    SplitscreenInfo[ECustomSplitScreenType::OneAndOneValance].PlayerData.Add(FPerPlayerSplitscreenData ( 0.5f , 1.00f , 0.00f , 0.00f )); // Player 1
    SplitscreenInfo[ECustomSplitScreenType::OneAndOneValance].PlayerData.Add(FPerPlayerSplitscreenData ( 0.5f , 1.00f , 0.5f , 0.00f)); // Player 2
}


void UCustomGameViewportClient::UpdateLayoutWithNewRatio ( float a, float b )
{   
    this->MayView = a;
    this->CodyView = b;
    SplitscreenInfo[ECustomSplitScreenType::OneAndOneValance].PlayerData[0] = FPerPlayerSplitscreenData ( this->MayView , 1.00f , 0.00f , 0.00f ); // Player 1
    SplitscreenInfo[ECustomSplitScreenType::OneAndOneValance].PlayerData[1] = FPerPlayerSplitscreenData ( this->CodyView , 1.00f , this->MayView , 0.00f ); // Player 2

    LayoutPlayers ( );
}

void UCustomGameViewportClient::UpdateActiveSplitscreenType ( )
{
    const int32 NumPlayers = GEngine->GetNumGamePlayers ( GetWorld ( ) );

    if ( NumPlayers == 2 )
    {
        ActiveSplitscreenType = static_cast<ESplitScreenType::Type>(ECustomSplitScreenType::OneAndOneValance);
    }
    else
    {
        // 기본 처리
        Super::UpdateActiveSplitscreenType ( );
    }
}