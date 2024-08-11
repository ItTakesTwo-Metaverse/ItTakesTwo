// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "CSR_P_AComp_InputBInd.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MTVS_ITTAKESTWO_API UCSR_P_AComp_InputBInd : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSR_P_AComp_InputBInd();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
// owner 캐릭터
	UPROPERTY ( EditDefaultsOnly )
	class ACSR_P_Player* Character_;

	virtual void SetupInputComponent (class UEnhancedInputComponent* EnhancedInputComponent );

// 이동 키 입력
	UPROPERTY ( EditDefaultsOnly , Category = "ModifyAble" )
	class UInputAction* IA_CMove_;

	void InputMove( const FInputActionValue& Value );

// 마우스, 조이스틱 오른쪽 입력
	UPROPERTY ( EditDefaultsOnly , Category = "ModifyAble" )
	class UInputAction* IA_CLook_;

	void InputLook( const FInputActionValue& Value );

// 점프 키 입력
	UPROPERTY ( EditDefaultsOnly , Category = "ModifyAble" )
	class UInputAction* IA_CJump_;

	void InputJump( const FInputActionValue& Value );

	UPROPERTY ( EditDefaultsOnly , Category = "ModifyAble" )
	class UInputAction* IA_CRun_;

	void OnRunToggleButton( const FInputActionValue& Value );

	void OffRunToggleButton( const FInputActionValue& Value );
};

