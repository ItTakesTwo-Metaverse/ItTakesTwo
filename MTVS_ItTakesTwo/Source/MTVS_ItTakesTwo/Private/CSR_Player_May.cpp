// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_Player_May.h"
#include "Kismet/GameplayStatics.h"
#include "CSR_FunctionLib.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

void ACSR_Player_May::BeginPlay()
{
	Super::BeginPlay();
	this->MakeEnhancedInputLocalSubSystem();
}

// PlayerController�� IMC_PlayerController�� ����.
void ACSR_Player_May::MakeEnhancedInputLocalSubSystem()
{
	// �ش� Mannger�� ��Ʈ�ѷ��� �����ϴ��� Ȯ���մϴ�.
	APlayerController* Player_1 = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	if (Player_1 == nullptr)
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("Player_1 is null"));

	// EnhancedInput�� �����մϴ�.
	UEnhancedInputLocalPlayerSubsystem* SubSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player_1->GetLocalPlayer());
	if (SubSys == nullptr)
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("SubSyn is null"));
	// EnhancedInput�� IMC_...�� �����մϴ�.
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
#pragma endregion EnhancedInput register

#pragma region

#pragma endregion Input Function binding
}


