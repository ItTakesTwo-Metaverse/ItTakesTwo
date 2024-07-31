// Fill out your copyright notice in the Description page of Project Settings.


#include "Trash/CSR_C_Player.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"

//void ACSR_C_Player::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

//void ACSR_C_Player::PossessedBy(AController* NewController)
//{
//	Super::PossessedBy(NewController);
//
//	SetupController();
//}

//void ACSR_C_Player::SetupController()
//{
//	
//	//if (this->Controller == nullptr) {
//	//	UE_LOG(LogTemp, Error, TEXT("CSR_PlayersManngerPawn : Controller is null"));
//	//	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
//	//}
//
//	////해당 Mannger의 컨트롤러를 플레이어컨트롤러로 Cast해줍니다.
//	//auto* pc = Cast<APlayerController>(this->Controller);
//	//// 해당 Mannger의 컨트롤러를 플레이어컨트롤러로 Cast해준 pc가 nullptr인지 확인합니다.
//	//if (pc == nullptr) {
//	//	UE_LOG(LogTemp, Error, TEXT("CSR_PlayersManngerPawn : pc is null"));
//	//	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
//	//}
//
//	////// EnhancedInput을 연결합니다.
//	//UEnhancedInputLocalPlayerSubsystem* SubSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
//	//if (SubSys == nullptr) {
//	//	UE_LOG(LogTemp, Error, TEXT("CSR_PlayersManngerPawn : SubSys is null"));
//	//	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
//	//}
//	////// EnhancedInput을 IMC_...를 맵핑합니다.
//	//SubSys->AddMappingContext(IMC_PlayerController, 0);
//}

//void ACSR_C_Player::SetupEnhancedInput(UInputComponent* NewInputComponent)
//{
//    if (NewInputComponent == nullptr)
//    {
//        UE_LOG(LogTemp, Error, TEXT("ACSR_C_Player : InputComponent is null"));
//        UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
//    }
//    UEnhancedInputComponent *InputKey = CastChecked<UEnhancedInputComponent>(NewInputComponent);
//    if (InputKey == nullptr) {
//        UE_LOG(LogTemp, Error, TEXT("ACSR_C_Player : InputKey is null"));
//        UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
//    }
//    //InputKey->BindAction(IA_Horizon, ETriggerEvent::Triggered, this, &ACSR_C_Player::HorMove);
//}

//void ACSR_C_Player::HorMove(const FInputActionValue& value)
//{
//	float v = value.Get<float>();
//	UE_LOG(LogTemp, Warning, TEXT("ACSR_C_Player : Move, %f"), v);
//}

//void ACSR_C_Player::initCharacter(class UInputComponent* MainPlayerInputComponent)
//{
//	if (MainPlayerInputComponent == nullptr) {
//		UE_LOG(LogTemp, Error, TEXT("ACSR_C_Player : InputKey is null"));
//		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
//	}
//	UEnhancedInputComponent *InputKey = CastChecked<UEnhancedInputComponent>(MainPlayerInputComponent);
//	if (InputKey == nullptr) {
//		UE_LOG(LogTemp, Error, TEXT("ACSR_C_Player : InputKey is null"));
//		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
//	}
//	InputKey->BindAction(this->IA_Horizon_P1, ETriggerEvent::Started, this, &ACSR_C_Player::HorMove);
//}
//

