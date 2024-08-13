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
	UPROPERTY( EditAnywhere, Category = "ModifyAble" )
	int32 MaxHp = 8;

	UPROPERTY( EditAnywhere )
	int32 CurHp = MaxHp;

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

	UPROPERTY(EditDefaultsOnly)
	FVector SavePoint = FVector::ZeroVector;

	UPROPERTY( EditDefaultsOnly , Category = "ModifyAble")
	float CurrentTIme = 0;

	UPROPERTY( EditDefaultsOnly , Category = "ModifyAble")
	float DieTime = 3.0f;
	
	UPROPERTY ( EditDefaultsOnly , Category = "ModifyAble" )
	float INVItime = 100.0f;
	

	UPROPERTY ( EditDefaultsOnly , Category = "ModifyAble" )
	class UNiagaraSystem* NiagaraEffect;

	UPROPERTY( )
	int32 PlayerIndex;
	

	void Setting( );

	virtual void Landed ( const FHitResult& Hit ) override;

	UFUNCTION(BlueprintCallable, Category = "MyCategory") 
	void fallingUnder( );
	
	void OnDamaged(int32 Damage);

#pragma endregion ComponentSetting

#pragma region
	//UPROPERTY ( EditDefaultsOnly )
	//class UCSR_P_AComp_InputBInd* KeyBindComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "ModifyAble" )
	class UInputMappingContext *IMC_PlayerController_;
#pragma endregion KeyBind
	
	void SecondJumpToOtherComp( );

	//virtual void OnMyBoxBeginOverLap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );
};
