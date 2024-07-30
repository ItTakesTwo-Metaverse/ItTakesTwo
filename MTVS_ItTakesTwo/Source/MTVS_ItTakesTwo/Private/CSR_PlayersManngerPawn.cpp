// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_PlayersManngerPawn.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

// Sets default values
ACSR_PlayersManngerPawn::ACSR_PlayersManngerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}
// Called when the game starts or when spawned
void ACSR_PlayersManngerPawn::BeginPlay()
{
	Super::BeginPlay();
	// enhanced�� ����ϱ� ���� �غ�
	this->MakeEnhancedInputLocalSubSystem();
}

// Called every frame
void ACSR_PlayersManngerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACSR_PlayersManngerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* InputKey = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (InputKey == nullptr) {
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}
	InputKey->BindAction(this->SELF_CreateCharactorButton, ETriggerEvent::Started, this, &ACSR_PlayersManngerPawn::SpawnPlayers);
}

// EnhancedInput�� ����ϱ����� �÷��̾� ��Ʈ�ѷ��� �����ͼ� ���� ������ IMC�� �������ִ� �۾��� �Ѵ�.
void ACSR_PlayersManngerPawn::MakeEnhancedInputLocalSubSystem()
{
	auto* pc = Cast<APlayerController>(this->Controller);
	if (pc == nullptr) {
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}
	UEnhancedInputLocalPlayerSubsystem* SubSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
	if (SubSys == nullptr) {
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}
	SubSys->AddMappingContext(IMC_PlayerController, 0);
}

// Input ��ȣ�� ������ ĳ���͸� �����մϴ�.
void ACSR_PlayersManngerPawn::SpawnPlayers()
{
	// player�� �����Ѵ�.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CreateCharacter"));
	// ������ �÷��̾����� ���� �Ѱ��ش�.
}

