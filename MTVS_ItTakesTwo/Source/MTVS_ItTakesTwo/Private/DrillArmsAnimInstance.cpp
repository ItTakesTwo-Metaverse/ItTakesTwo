// Fill out your copyright notice in the Description page of Project Settings.


#include "DrillArmsAnimInstance.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"

void UDrillArmsAnimInstance::PlayDrillArmsMontage ( )
{
	Montage_Play ( DrillArmsMontage );
}

void UDrillArmsAnimInstance::PlayDrillArms_Attack4_Montage ( )
{
	Montage_Play ( DrillArms_Attack4_Montage );
}
