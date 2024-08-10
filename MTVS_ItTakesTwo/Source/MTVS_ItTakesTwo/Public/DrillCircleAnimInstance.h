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
	virtual void NativeInitializeAnimation ( ) override;

};
