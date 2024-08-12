// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_C_AComp_InputBIndCody.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "CSR_Player_Cody.h"
#include "CSR_CodyPile.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "CSR_FunctionLib.h"
#include "HSW_BulletManager.h"

void UCSR_C_AComp_InputBIndCody::BeginPlay ( )
{
	Super::BeginPlay ();
	this->CodyCharacter_ = Cast< ACSR_Player_Cody>(this->GetOwner());
	if ( this->CodyCharacter_ == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_C_AComp_InputBIndCody : this->CodyCharacter_ is null" ) );
	}
}

void UCSR_C_AComp_InputBIndCody::SetupInputComponent ( class UEnhancedInputComponent* InputKey )
{
	Super::SetupInputComponent (InputKey );

	InputKey->BindAction ( IA_CPile_ , ETriggerEvent::Started , this , &UCSR_C_AComp_InputBIndCody::ChangeZoomIn );
	InputKey->BindAction ( IA_CPile_ , ETriggerEvent::Completed , this , &UCSR_C_AComp_InputBIndCody::ChangeZoomOut );
	InputKey->BindAction ( IA_CFire , ETriggerEvent::Started , this , &UCSR_C_AComp_InputBIndCody::ExecFIre );
	InputKey->BindAction ( IA_CBack , ETriggerEvent::Started , this , &UCSR_C_AComp_InputBIndCody::ExecBack );
}

void UCSR_C_AComp_InputBIndCody::ChangeZoomIn ( )
{
	UE_LOG(LogTemp, Warning, TEXT("1234" ) );
	this->CodyCharacter_->CameraComp->bUsePawnControlRotation = true;
	this->CodyCharacter_->bUseControllerRotationYaw = true;
	this->CodyCharacter_->CodyPileComp->ToggleButton ( true );
	this->CodyCharacter_->CodyPileComp->NailBag->NailPop ( this->CodyCharacter_->ArrowComp->GetComponentLocation ( ) , this->CodyCharacter_->GetActorRotation ( ) );
}

void UCSR_C_AComp_InputBIndCody::ChangeZoomOut ( )
{
	this->CodyCharacter_->CameraComp->bUsePawnControlRotation = false;
	this->CodyCharacter_->bUseControllerRotationYaw = false;
	this->CodyCharacter_ ->CodyPileComp->ToggleButton ( false );
}

void UCSR_C_AComp_InputBIndCody::ExecFIre ( )
{
	this->CodyCharacter_->CodyPileComp->OnMyActionFire ( this->CodyCharacter_->ArrowComp->GetComponentLocation ( ) , this->CodyCharacter_->GetActorRotation ( ) );
}

void UCSR_C_AComp_InputBIndCody::ExecBack ( )
{
	this->CodyCharacter_->CodyPileComp->OnMyActionBack ( );
}
