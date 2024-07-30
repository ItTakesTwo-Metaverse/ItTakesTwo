// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSR_P_Player.h"
#include "CSR_Player_Cody.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API ACSR_Player_Cody : public ACSR_P_Player
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// possess ���� �߿��� �������� ���� �������̵�����.
	virtual void PossessedBy(AController* NewController) override;

	// PlayerController�� IMC_PlayerController�� ����.
	void MakeEnhancedInputLocalSubSystem();
#pragma region


	

#pragma endregion
};
