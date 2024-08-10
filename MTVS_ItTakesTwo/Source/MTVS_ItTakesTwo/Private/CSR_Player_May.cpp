﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_Player_May.h"
#include "Kismet/GameplayStatics.h"
#include "CSR_FunctionLib.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "CSR_P_AComp_InputBInd.h"
#include "CSR_C_AComp_InputBIndMay.h"

ACSR_Player_May::ACSR_Player_May ( )
{
	this->KeyBindComponent = CreateDefaultSubobject<UCSR_C_AComp_InputBIndMay> ( TEXT ( "KeyBindComponent" ) );

}

void ACSR_Player_May::BeginPlay()
{
	Super::BeginPlay();
	this->MakeEnhancedInputLocalSubSystem();
}

// PlayerController를 IMC_PlayerController와 맵핑.

void ACSR_Player_May::MakeEnhancedInputLocalSubSystem()
{
	// 해당 Mannger의 컨트롤러가 존재하는지 확인합니다.
	APlayerController* Player_1 = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	if ( Player_1 == nullptr ) {
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("Player_1 is null"));
	}

	// EnhancedInput을 연결합니다.
	UEnhancedInputLocalPlayerSubsystem* SubSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player_1->GetLocalPlayer());
	if ( SubSys == nullptr ) {
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("SubSyn is null"));
	}
	// EnhancedInput을 IMC_...를 맵핑합니다.
	SubSys->AddMappingContext(this->IMC_PlayerController_, 0);
}


void ACSR_Player_May::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACSR_Player_May::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
#pragma region
	UEnhancedInputComponent* InputKey = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (InputKey == nullptr) {
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("ACSR_Player_May : InputKey is null"));
	}

	this->KeyBindComponent->SetupInputComponent( InputKey );
#pragma endregion EnhancedInput register

	Setting ( );
}


