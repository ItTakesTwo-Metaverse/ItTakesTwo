// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSR_P_AComp_InputBInd.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "CSR_C_AComp_InputBIndMay.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API UCSR_C_AComp_InputBIndMay : public UCSR_P_AComp_InputBInd
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay ( ) override;

	virtual void SetupInputComponent ( class UEnhancedInputComponent* InputKey ) override;

	UPROPERTY ( EditDefaultsOnly )
	class ACSR_Player_May* MayCharacter_;

	UPROPERTY(EditDefaultsOnly )
	class AHSW_Hammer* Hammer;

	UPROPERTY(EditDefaultsOnly, Category = "ModifyAble" )
	class UInputAction	*IA_CATTACK_;

	void OnAttackAction(const FInputActionValue& Value );
};
