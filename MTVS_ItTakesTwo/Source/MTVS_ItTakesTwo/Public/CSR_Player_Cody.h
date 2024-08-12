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
public:
	ACSR_Player_Cody ( );
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// possess 과정 중에서 벌어지는 일을 오버라이드했음.
	virtual void PossessedBy(AController* NewController) override;

	// PlayerController를 IMC_PlayerController와 맵핑.
	void MakeEnhancedInputLocalSubSystem();


public:
#pragma region
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "ModifyAble" )
	class UCSR_CodyPile* CodyPileComp;

	UPROPERTY(EditDefaultsOnly );
	class UArrowComponent * ArrowComp;

	UPROPERTY ( EditDefaultsOnly )
	class UCSR_C_AComp_InputBIndCody* KeyBindComponent;

	UPROPERTY()
	class UCSR_CodyAnimation *AnimCody;

	UPROPERTY(EditDefaultsOnly )
	class USceneComponent *NailBagLocation;

#pragma endregion PileMovement;
};
