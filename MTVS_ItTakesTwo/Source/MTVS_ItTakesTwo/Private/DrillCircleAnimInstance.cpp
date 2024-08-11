// Fill out your copyright notice in the Description page of Project Settings.


#include "DrillCircleAnimInstance.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"



void UDrillCircleAnimInstance::PlayDrillCircle1Montage ( )
{
	Montage_Play ( DrillCircle1Montage ); 

	GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "Play Drill Circle1111 Montage" ) );
	UE_LOG ( LogTemp , Warning , TEXT ( "Play Drill Circle1111 Montage" ) );
}

void UDrillCircleAnimInstance::PlayDrillCircle2Montage ( )
{
	Montage_Play ( DrillCircle2Montage );

	GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "Play Drill Circle2222 Montage" ) );
	UE_LOG ( LogTemp , Warning , TEXT ( "Play Drill Circle2222 Montage" ) );
}

