﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_Player_Cody.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "CSR_FunctionLib.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "CSR_CodyPile.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "CSR_P_AComp_InputBInd.h"
#include "CSR_C_AComp_InputBIndCody.h"

ACSR_Player_Cody::ACSR_Player_Cody ( )
{
	this->CodyPileComp = CreateDefaultSubobject< UCSR_CodyPile> ( TEXT ( "CodyPileComp" ) );
	if ( this->CodyPileComp == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "ACSR_Player_Cody : this->CodyPileComp is null" ) );
	}
	this->CodyPileComp->InitComp ( this->CameraComp , this->SpringArmComp, this->SpringArmComp->TargetArmLength, this );

	this->ArrowComp = CreateDefaultSubobject<UArrowComponent> ( TEXT ( "ArrowComp" ) );
	if ( this->ArrowComp == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "ACSR_Player_Cody : this->ArrowComp is null" ) );
	}
	this->ArrowComp->SetupAttachment ( RootComponent );
	this->ArrowComp->SetRelativeLocation ( FVector ( 0 , 70.0f , 70.0f ) );
	this->KeyBindComponent = CreateDefaultSubobject<UCSR_C_AComp_InputBIndCody> ( TEXT ( "KeyBindComponent" ) );
}

void ACSR_Player_Cody::BeginPlay()
{
	Super::BeginPlay();
}

// possess 과정 중에서 선 입력
void ACSR_Player_Cody::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	MakeEnhancedInputLocalSubSystem();
}

// PlayerController를 IMC_PlayerController와 맵핑.
void ACSR_Player_Cody::MakeEnhancedInputLocalSubSystem()
{
	APlayerController* Player_2 = UGameplayStatics::GetPlayerController(this->GetWorld(), 1);
	if (Player_2 == nullptr)
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("Player_2 is null"));

	// EnhancedInput을 연결합니다.
	UEnhancedInputLocalPlayerSubsystem* SubSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player_2->GetLocalPlayer());
	if ( SubSys == nullptr ) {
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("SubSyn is null"));
	}

	// EnhancedInput을 IMC_...를 맵핑합니다.
	SubSys->AddMappingContext(this->IMC_PlayerController_, 0);
}

void ACSR_Player_Cody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACSR_Player_Cody::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
#pragma region
	UEnhancedInputComponent* InputKey = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (InputKey == nullptr) {
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("ACSR_Player_Cody : InputKey is null"));
	}

	this->KeyBindComponent->SetupInputComponent ( InputKey );
#pragma endregion EnhancedInput register

	Setting ( );
}

