// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSR_P_Player.h"
#include "CSR_Player_May.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API ACSR_Player_May : public ACSR_P_Player
{
	GENERATED_BODY()
public:
	ACSR_Player_May ( );
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// PlayerController를 IMC_PlayerController와 맵핑.
	void MakeEnhancedInputLocalSubSystem();
#pragma region
public:
	UPROPERTY ( EditDefaultsOnly )
	class UCSR_C_AComp_InputBIndMay* KeyBindComponent;




#pragma endregion
};
