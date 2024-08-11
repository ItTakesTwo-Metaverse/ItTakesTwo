// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CSR_BaseAnimation.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API UCSR_BaseAnimation : public UAnimInstance
{
	GENERATED_BODY()
public:

	virtual void NativeInitializeAnimation ( ) override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	// Vertical;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//bool IsInAir;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//bool IsCrouched;


	//// anim 몽타주를 플레이하고 싶다.
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//class UAnimMontage *FireMontage;

	//void PlayerFireMontage();

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//class UAnimMontage *DiveRollMontage;

	//void PlayerDiveRollMontage();
};
