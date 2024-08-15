// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_C_AComp_InputBIndCody.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "CSR_Player_Cody.h"
#include "CSR_CodyPile.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "CSR_FunctionLib.h"
#include "HSW_BulletManager.h"
#include "HSW_Bullet.h"

void UCSR_C_AComp_InputBIndCody::BeginPlay ( )
{
	Super::BeginPlay ();
	this->CodyCharacter_ = Cast< ACSR_Player_Cody>(this->GetOwner());
	if ( this->CodyCharacter_ == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_C_AComp_InputBIndCody : this->CodyCharacter_ is null" ) );
	}

	NailBag = CodyCharacter_->CodyPileComp->NailBag;
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
	Nail = this->CodyCharacter_->CodyPileComp->NailBag->NailPop ( );
	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Green , Nail->GetName());
	if ( Nail == nullptr ) {
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "Zoom In: Nail NULL" ));
		return;
	}
	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "Zoom In: Nail Vaild" ) );
	this->CodyCharacter_->CameraComp->bUsePawnControlRotation = true;
	this->CodyCharacter_->bUseControllerRotationYaw = true;
	this->CodyCharacter_->CodyPileComp->ToggleButton ( true );

	Nail->SetState (ENailState::LOAD );
	//this->CodyCharacter_->ArrowComp->GetComponentLocation ( ) , this->CodyCharacter_->GetActorRotation ( )
}

void UCSR_C_AComp_InputBIndCody::ChangeZoomOut ( )
{
	this->CodyCharacter_->CameraComp->bUsePawnControlRotation = false;
	this->CodyCharacter_->bUseControllerRotationYaw = false;
	this->CodyCharacter_ ->CodyPileComp->ToggleButton ( false );

	if ( Nail == nullptr )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "Zoom Out: Nail NULL" ) );
		return;
	}

	//this->CodyCharacter_->CodyPileComp->NailBag->NailPush (Nail);

	if ( Nail->State == ENailState::LOAD )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "Zoomout Return" ) );
		NailBag->NailPush ( Nail );
		Nail->SetState ( ENailState::BASIC );
		Nail = nullptr;
	}
}

void UCSR_C_AComp_InputBIndCody::ExecFIre ( )
{
	//Nail = GrabbedNail;
	if ( Nail == nullptr )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Can't ExecFire" ) );
		return;
	}
	this->CodyCharacter_->CodyPileComp->OnMyActionFire ( this->CodyCharacter_->ArrowComp->GetComponentLocation ( ) , this->CodyCharacter_->GetActorRotation ( ));
}

void UCSR_C_AComp_InputBIndCody::ExecBack ( )
{
	this->CodyCharacter_->CodyPileComp->OnMyActionBack ( );
}
