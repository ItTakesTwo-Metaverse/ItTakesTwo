// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LockHP.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API ULockHP : public UUserWidget
{
	GENERATED_BODY()
public:


	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPBar;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void SetHPBar ( float cur , float max );
};
