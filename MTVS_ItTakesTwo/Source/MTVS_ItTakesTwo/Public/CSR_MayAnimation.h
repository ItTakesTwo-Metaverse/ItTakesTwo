// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSR_BaseAnimation.h"
#include "CSR_MayAnimation.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API UCSR_MayAnimation : public UCSR_BaseAnimation
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation ( ) override;

	virtual void NativeUpdateAnimation ( float DeltaSeconds ) override;

	UPROPERTY ( EditDefaultsOnly )
	class ACSR_Player_May* Player;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Speed = 0;
	
	// Horizontal
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Direction = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsInAir =false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsCrouched = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAnimMontage *AttackMontage;

	UFUNCTION()
	void AnimNotify_HammerAttach();

	UFUNCTION()
	void AnimNotify_HammerDetach();

	void PlayerAttackMontage();

};
