﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RightArmAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ERightArmAnimState : uint8
{  
	Start ,
	Idle ,
	CoolDown ,
	Attack1 ,
	Paused ,
	Attack2 ,
	Attack3 ,
	Attack4 ,
	Attack5
	
};

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API URightArmAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:

	URightArmAnimInstance ( );

	virtual void NativeInitializeAnimation () override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY( )
	class AToolboxBoss* me;

	UFUNCTION(BlueprintCallable)
	void SetAnimState( ERightArmAnimState NewState);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ERightArmAnimState AnimState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	bool bIsAttacking1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	bool bIsPausing;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	bool bIsAttacking2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	bool bIsAttacking3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	bool bIsAttacking4;

};
