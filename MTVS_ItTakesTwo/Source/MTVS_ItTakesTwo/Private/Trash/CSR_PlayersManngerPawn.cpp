// Fill out your copyright notice in the Description page of Project Settings.


#include "Trash/CSR_PlayersManngerPawn.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "Trash/CSR_C_Player.h"
#include "CSR_FunctionLib.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"

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
	this->PlayerInputComp = PlayerInputComponent;
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// EnhancedInput�� �����մϴ�.
	this->InputKey = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (this->InputKey == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("CSR_PlayersManngerPawn : InputKey is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	
	this->InputKey->BindAction(this->onrizon_P1, ETriggerEvent::Started, this, &ACSR_PlayersManngerPawn::MoveP1);
	// ĳ���� ���� Ű(P)�� ���ε��մϴ�.
	this->InputKey->BindAction(this->SELF_CreateCharact, ETriggerEvent::Started, this, &ACSR_PlayersManngerPawn::SpawnPlayers);
	//this->InputKey->BindAction(this->onrizon_P2, ETriggerEvent::Started, this, &ACSR_PlayersManngerPawn::MoveP1);

}
 
// EnhancedInput�� ����ϱ����� �÷��̾� ��Ʈ�ѷ��� �����ͼ� ���� ������ IMC�� �������ִ� �۾��� �Ѵ�.
void ACSR_PlayersManngerPawn::MakeEnhancedInputLocalSubSystem()
{
	// �ش� Mannger�� ��Ʈ�ѷ��� �����ϴ��� Ȯ���մϴ�.
	if (this->Controller == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("CSR_PlayersManngerPawn : Controller is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	// �ش� Mannger�� ��Ʈ�ѷ��� �÷��̾���Ʈ�ѷ��� Cast���ݴϴ�.
	auto* pc = Cast<APlayerController>(this->Controller);
	// �ش� Mannger�� ��Ʈ�ѷ��� �÷��̾���Ʈ�ѷ��� Cast���� pc�� nullptr���� Ȯ���մϴ�.
	if (pc == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("CSR_PlayersManngerPawn : pc is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	// EnhancedInput�� �����մϴ�.
	UEnhancedInputLocalPlayerSubsystem* SubSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
	if (SubSys == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("CSR_PlayersManngerPawn : SubSys is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}
	// EnhancedInput�� IMC_...�� �����մϴ�.
	SubSys->AddMappingContext(IMC_PlayerController, 0);
}

void ACSR_PlayersManngerPawn::MoveP1(const FInputActionValue& value)
{
	//this->P1_Cody->HorMove(value);
}

// Input ��ȣ�� ������ ĳ���͸� �����մϴ�.
void ACSR_PlayersManngerPawn::SpawnPlayers()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CreateCharacter"));
	// PlayerStart ��ġ�� ã���ϴ�.
	//FTransform CodyTrans = UCSR_FunctionLib::FindStartTransForm(this, FString("Cody"));
	//FTransform MayTrans = UCSR_FunctionLib::FindStartTransForm(this, FString("May"));

	TArray<AActor*> P1List;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), TEXT("P1"), P1List);

	TArray<AActor*> P2List;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), TEXT("P2"), P2List);

	FTransform CodyTrans = P1List[0]->GetActorTransform();
	FTransform MayTrans = P2List[0]->GetActorTransform();
	
	// P1 player�� �����Ѵ�.
	APlayerController * P1_controller = UGameplayStatics::CreatePlayer(this->GetWorld(), 1, true);
	this->P1 = P1_controller;
	if (P1_controller == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("CSR_PlayersManngerPawn : P2_controller is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	// Cody ĳ���͸� �����մϴ�.
	P1_Cody = GetWorld()->SpawnActor<ACSR_C_Player>(SpawnCharactorA, CodyTrans);
	if (P1_Cody == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("CSR_PlayersManngerPawn : P1_Cody is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	// ������ Cody �÷��̾����� P1 ��Ʈ�ѷ��� Possess�մϴ�.
	P1_controller->Possess(P1_Cody);
	
	//P1_Cody->SetupEnhancedInput(this->PlayerInputComp);
	//UEnhancedInputLocalPlayerSubsystem* P1_SubSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(P1_controller->GetLocalPlayer());
	//if (P1_SubSys == nullptr) {
	//	UE_LOG(LogTemp, Warning, TEXT("CSR_PlayersManngerPawn : P1_SubSys is null"));
	//	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	//}
	//P1_SubSys->AddMappingContext(IMC_PlayerController, 0);

	// P2 player�� �����Ѵ�.
	APlayerController* P2_controller = UGameplayStatics::CreatePlayer(this->GetWorld(), 2, true);
	if (P2_controller == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("CSR_PlayersManngerPawn : P2_controller is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	// May ĳ���͸� �����մϴ�.
	P2_May = GetWorld()->SpawnActor<ACSR_C_Player>(SpawnCharactorB, MayTrans);
	if (P2_May == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("CSR_PlayersManngerPawn : P1_Cody is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	// ������ May �÷��̾����� P2 ��Ʈ�ѷ��� Possess�մϴ�.
	P2_controller->Possess(P2_May);
	//P2_May->SetupController();
	//P2_May->SetupEnhancedInput(this->PlayerInputComp);
	//UEnhancedInputLocalPlayerSubsystem* P2_SubSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(P2_controller->GetLocalPlayer());
	//if (P2_SubSys == nullptr) {
	//	UE_LOG(LogTemp, Warning, TEXT("CSR_PlayersManngerPawn : P2_SubSys is null"));
	//	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	//}
	//P2_SubSys->AddMappingContext(IMC_PlayerController, 0);
	//P2_May->initCharacter(P2_controller->InputComponent);

}

