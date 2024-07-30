// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "CSR_PlayersManngerPawn.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API ACSR_PlayersManngerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACSR_PlayersManngerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
#pragma region
	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext *IMC_PlayerController;
	// 캐릭터 생성 액션 버튼
	UPROPERTY(EditDefaultsOnly)
	class UInputAction *onrizon_P1;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction *SELF_CreateCharact;

	//UPROPERTY(EditInstanceOnly)
	//class UInputAction * onrizon_P2;

	UPROPERTY(EditDefaultsOnly)
	class UInputComponent *PlayerInputComp;

	UPROPERTY(EditDefaultsOnly)
	class UEnhancedInputComponent* InputKey;

	UPROPERTY(EditDefaultsOnly)
	class APlayerController* P1;

	void MakeEnhancedInputLocalSubSystem();
	


#pragma endregion KeyMappingHeader

public:
#pragma region
	// 블루프린트에 값 바인딩 해야하는 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ACSR_C_Player> SpawnCharactorA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ACSR_C_Player> SpawnCharactorB;

	class ACSR_C_Player *P1_Cody;
	class ACSR_C_Player *P2_May;
	// 함수
	void SpawnPlayers();
	void MoveP1(const FInputActionValue& value);
#pragma endregion createPlayerHeader
};
