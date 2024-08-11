// Fill out your copyright notice in the Description page of Project Settings.


#include "DrillCircleAnimInstance.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"



void UDrillCircleAnimInstance::PlayDrillCircle1Montage ( )
{
	Montage_Play ( DrillCircle1Montage );
}

void UDrillCircleAnimInstance::PlayDrillCircle2Montage ( )
{
	Montage_Play ( DrillCircle2Montage );
}

