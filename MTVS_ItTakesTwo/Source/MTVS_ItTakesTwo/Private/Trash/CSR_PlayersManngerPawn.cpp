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
	// enhanced를 사용하기 위한 준비
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

	// EnhancedInput을 연결합니다.
	this->InputKey = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (this->InputKey == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("CSR_PlayersManngerPawn : InputKey is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	
	this->InputKey->BindAction(this->onrizon_P1, ETriggerEvent::Started, this, &ACSR_PlayersManngerPawn::MoveP1);
	// 캐릭터 생성 키(P)를 바인딩합니다.
	this->InputKey->BindAction(this->SELF_CreateCharact, ETriggerEvent::Started, this, &ACSR_PlayersManngerPawn::SpawnPlayers);
	//this->InputKey->BindAction(this->onrizon_P2, ETriggerEvent::Started, this, &ACSR_PlayersManngerPawn::MoveP1);

}
 
// EnhancedInput을 사용하기위해 플레이어 컨트롤러를 가져와서 내가 설정한 IMC와 맵핑해주는 작업을 한다.
void ACSR_PlayersManngerPawn::MakeEnhancedInputLocalSubSystem()
{
	// 해당 Mannger의 컨트롤러가 존재하는지 확인합니다.
	if (this->Controller == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("CSR_PlayersManngerPawn : Controller is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	// 해당 Mannger의 컨트롤러를 플레이어컨트롤러로 Cast해줍니다.
	auto* pc = Cast<APlayerController>(this->Controller);
	// 해당 Mannger의 컨트롤러를 플레이어컨트롤러로 Cast해준 pc가 nullptr인지 확인합니다.
	if (pc == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("CSR_PlayersManngerPawn : pc is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	// EnhancedInput을 연결합니다.
	UEnhancedInputLocalPlayerSubsystem* SubSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
	if (SubSys == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("CSR_PlayersManngerPawn : SubSys is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}
	// EnhancedInput을 IMC_...를 맵핑합니다.
	SubSys->AddMappingContext(IMC_PlayerController, 0);
}

void ACSR_PlayersManngerPawn::MoveP1(const FInputActionValue& value)
{
	//this->P1_Cody->HorMove(value);
}

// Input 신호가 들어오면 캐릭터를 생성합니다.
void ACSR_PlayersManngerPawn::SpawnPlayers()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CreateCharacter"));
	// PlayerStart 위치를 찾습니다.
	//FTransform CodyTrans = UCSR_FunctionLib::FindStartTransForm(this, FString("Cody"));
	//FTransform MayTrans = UCSR_FunctionLib::FindStartTransForm(this, FString("May"));

	TArray<AActor*> P1List;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), TEXT("P1"), P1List);

	TArray<AActor*> P2List;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), TEXT("P2"), P2List);

	FTransform CodyTrans = P1List[0]->GetActorTransform();
	FTransform MayTrans = P2List[0]->GetActorTransform();
	
	// P1 player를 생성한다.
	APlayerController * P1_controller = UGameplayStatics::CreatePlayer(this->GetWorld(), 1, true);
	this->P1 = P1_controller;
	if (P1_controller == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("CSR_PlayersManngerPawn : P2_controller is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	// Cody 캐릭터를 생성합니다.
	P1_Cody = GetWorld()->SpawnActor<ACSR_C_Player>(SpawnCharactorA, CodyTrans);
	if (P1_Cody == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("CSR_PlayersManngerPawn : P1_Cody is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	// 생성된 Cody 플레이어한테 P1 컨트롤러를 Possess합니다.
	P1_controller->Possess(P1_Cody);
	
	//P1_Cody->SetupEnhancedInput(this->PlayerInputComp);
	//UEnhancedInputLocalPlayerSubsystem* P1_SubSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(P1_controller->GetLocalPlayer());
	//if (P1_SubSys == nullptr) {
	//	UE_LOG(LogTemp, Warning, TEXT("CSR_PlayersManngerPawn : P1_SubSys is null"));
	//	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	//}
	//P1_SubSys->AddMappingContext(IMC_PlayerController, 0);

	// P2 player를 생성한다.
	APlayerController* P2_controller = UGameplayStatics::CreatePlayer(this->GetWorld(), 2, true);
	if (P2_controller == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("CSR_PlayersManngerPawn : P2_controller is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	// May 캐릭터를 생성합니다.
	P2_May = GetWorld()->SpawnActor<ACSR_C_Player>(SpawnCharactorB, MayTrans);
	if (P2_May == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("CSR_PlayersManngerPawn : P1_Cody is null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}

	// 생성된 May 플레이어한테 P2 컨트롤러를 Possess합니다.
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

