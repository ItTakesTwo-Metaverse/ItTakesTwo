// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DrillCircleAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API UDrillCircleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	class UAnimMontage* DrillCircle1Montage;

	void PlayDrillCircle1Montage( );

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	class UAnimMontage* DrillCircle2Montage;

	void PlayDrillCircle2Montage( );

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	class UAnimMontage* DrillCircle2_Attack4_Montage;

	void PlayDrillCircle2_Attack4_Montage( );
};
