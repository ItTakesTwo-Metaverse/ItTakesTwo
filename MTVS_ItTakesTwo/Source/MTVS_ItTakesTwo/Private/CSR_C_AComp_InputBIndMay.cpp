// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_C_AComp_InputBIndMay.h"
#include "CSR_Player_May.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

void UCSR_C_AComp_InputBIndMay::BeginPlay ( )
{
	Super::BeginPlay ();
	this->CodyCharacter_ = Cast< ACSR_Player_May> ( this->GetOwner ( ) );
}

void UCSR_C_AComp_InputBIndMay::SetupInputComponent ( class UEnhancedInputComponent* InputKey )
{
	Super::SetupInputComponent ( InputKey );


}
