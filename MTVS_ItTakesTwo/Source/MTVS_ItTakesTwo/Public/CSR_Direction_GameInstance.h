// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CSR_Direction_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API UCSR_Direction_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	// 8방향 벡터를 저장합니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Directions")
    TArray<FVector2D> Directions;

    virtual void Init() override;
};
