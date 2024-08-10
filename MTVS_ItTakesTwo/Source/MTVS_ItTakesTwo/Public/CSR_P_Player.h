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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent *SpringArmComp;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent *CameraComp;

	UPROPERTY ( EditAnywhere , BlueprintReadWrite, Category="ModifyAble" )
	float EarlyCameraDistance = 1000;

	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "ModifyAble" )
	float EarlyCameraArmRotateHeight = 20;

	UPROPERTY(EditDefaultsOnly)
	class UCSR_P_AComp_CharicStateMannage *CharacterStateMannageComp;

	UPROPERTY(EditDefaultsOnly)
	class UCSR_P_AComp_CharicMovement *CharicMovementComp;

	UPROPERTY( EditDefaultsOnly )
	class UCSR_P_AComp_CameraMove *CameraMomveComp;

	UPROPERTY( EditDefaultsOnly )
	class UCSR_P_AComp_CharicJump *CharicJumpComp;

	UPROPERTY(EditDefaultsOnly)
	class UCharacterMovementComponent *CharacterStateComp;

	void Setting( );

	virtual void Landed ( const FHitResult& Hit ) override;
	
#pragma endregion ComponentSetting

#pragma region
	//UPROPERTY ( EditDefaultsOnly )
	//class UCSR_P_AComp_InputBInd* KeyBindComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "ModifyAble" )
	class UInputMappingContext *IMC_PlayerController_;
#pragma endregion KeyBind
	
	void SecondJumpToOtherComp( );
};
