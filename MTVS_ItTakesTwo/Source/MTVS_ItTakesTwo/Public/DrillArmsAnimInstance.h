// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DrillArmsAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API UDrillArmsAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	class UAnimMontage* DrillArmsMontage;

	void PlayDrillArmsMontage( );
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	class UAnimMontage* DrillArms_Attack4_Montage;

	void PlayDrillArms_Attack4_Montage( );
};
