// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_Player_Cody.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "CSR_FunctionLib.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

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
	if (SubSys == nullptr)
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("SubSyn is null"));
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
#pragma endregion EnhancedInput register
	
#pragma region
	InputKey->BindAction(Move_, ETriggerEvent::Triggered, this, &ACSR_P_Player::Player_Move);
	InputKey->BindAction(Look_ , ETriggerEvent::Triggered , this , &ACSR_P_Player::Player_View );

#pragma endregion Input Function binding
	this->AddControllerPitchInput (this->EarlyCameraArmRotateHeight);
}

