// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "CSR_P_Player.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API ACSR_P_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACSR_P_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

#pragma region
	// 플레이어 카메라 셋팅
	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent *SpringArmComp;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent *CameraComp;

#pragma endregion ComponentSetting

#pragma region
	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext *IMC_PlayerController_;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction	*Move_;

#pragma endregion KeyBind

#pragma region
	
	UPROPERTY(BlueprintReadOnly)
	FVector Direction;

	void Player_Move(const FInputActionValue& Value);
#pragma endregion PlayerMove
};
