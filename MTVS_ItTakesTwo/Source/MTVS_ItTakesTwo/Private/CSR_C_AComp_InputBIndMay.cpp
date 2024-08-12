// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_C_AComp_InputBIndMay.h"
#include "CSR_Player_May.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "CSR_MayUseHammerObj.h"
#include "CSR_FunctionLib.h"
#include "CSR_MayAnimation.h"

void UCSR_C_AComp_InputBIndMay::BeginPlay ( )
{
	Super::BeginPlay ();
	this->MayCharacter_ = Cast< ACSR_Player_May> ( this->GetOwner ( ) );
	if ( this->MayCharacter_ == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_C_AComp_InputBIndMay : this->MayCharacter_ is null" ) );
	}
}

void UCSR_C_AComp_InputBIndMay::SetupInputComponent ( class UEnhancedInputComponent* InputKey )
{
	Super::SetupInputComponent ( InputKey );
	
	InputKey->BindAction ( IA_CATTACK_ , ETriggerEvent::Started , this , &UCSR_C_AComp_InputBIndMay::OnAttackAction );

}

void UCSR_C_AComp_InputBIndMay::OnAttackAction ( const FInputActionValue& Value )
{
	UCSR_FunctionLib::PrintWindow(TEXT("heelo"));
	this->MayCharacter_->AnimMay->PlayerAttackMontage( );
}
