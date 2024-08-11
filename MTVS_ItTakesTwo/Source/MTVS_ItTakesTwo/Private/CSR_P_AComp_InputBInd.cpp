// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_P_AComp_InputBInd.h"
#include "CSR_FunctionLib.h"
#include "CSR_P_Player.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "CSR_P_AComp_CharicMovement.h"
#include "CSR_P_AComp_CameraMove.h"
#include "CSR_P_AComp_CharicJump.h"

// Sets default values for this component's properties
UCSR_P_AComp_InputBInd::UCSR_P_AComp_InputBInd()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCSR_P_AComp_InputBInd::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// owner 캐릭터 등록
	this->Character_ = Cast<ACSR_P_Player> ( this->GetOwner ( ) );
	if ( this->Character_ == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_P_AComp_InputBInd : this->Character_ is null" ) );
	}
}

void UCSR_P_AComp_InputBInd::SetupInputComponent ( class UEnhancedInputComponent* InputKey )
{
	if ( InputKey == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld (), FString ( "UCSR_P_AComp_InputBInd : EnhancedInputComponent is null" ) );
	}
	InputKey->BindAction ( IA_CMove_ , ETriggerEvent::Triggered , this , &UCSR_P_AComp_InputBInd::InputMove );
	InputKey->BindAction ( IA_CLook_ , ETriggerEvent::Triggered , this , &UCSR_P_AComp_InputBInd::InputLook );
	InputKey->BindAction ( IA_CJump_ , ETriggerEvent::Started , this , &UCSR_P_AComp_InputBInd::InputJump );
	InputKey->BindAction (	IA_CRun_ , ETriggerEvent::Started , this ,&UCSR_P_AComp_InputBInd::OnRunToggleButton );
	InputKey->BindAction ( IA_CRun_ , ETriggerEvent::Completed , this , &UCSR_P_AComp_InputBInd::OffRunToggleButton );
}

void UCSR_P_AComp_InputBInd::InputMove ( const FInputActionValue& Value )
{
	this->Character_->CharicMovementComp->PlayerMoveSelect( Value );
}

void UCSR_P_AComp_InputBInd::InputLook ( const FInputActionValue& Value )
{
	this->Character_->CameraMomveComp->Player_View ( Value );
}

void UCSR_P_AComp_InputBInd::InputJump ( const FInputActionValue& Value )
{
	this->Character_->CharicJumpComp->PlayerJump( Value );
}

void UCSR_P_AComp_InputBInd::OnRunToggleButton ( const FInputActionValue& Value )
{
	this->Character_->CharicMovementComp->RunStart( Value );
}

void UCSR_P_AComp_InputBInd::OffRunToggleButton ( const FInputActionValue& Value )
{
	this->Character_->CharicMovementComp->RunEnd ( Value );
}
