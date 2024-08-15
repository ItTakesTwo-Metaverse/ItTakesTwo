// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_Player_May.h"
#include "Kismet/GameplayStatics.h"
#include "CSR_FunctionLib.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "CSR_P_AComp_InputBInd.h"
#include "CSR_C_AComp_InputBIndMay.h"
#include "CSR_MayUseHammerObj.h"
#include "Components/SceneComponent.h"
#include "CSR_MayAnimation.h"
#include "HSW_Hammer.h"
#include "SCR_ItTakesTwoGameMode.h"
#include "CSR_PlayerWidget.h"

ACSR_Player_May::ACSR_Player_May ( )
{
	this->UseHammerComp = CreateDefaultSubobject< UCSR_MayUseHammerObj> ( TEXT ( "UseHammerComp" ) );
	if ( this->UseHammerComp == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "ACSR_Player_May : this->UseHammerComp is null" ) );
	}
	this->KeyBindComponent = CreateDefaultSubobject<UCSR_C_AComp_InputBIndMay> ( TEXT ( "KeyBindComponent" ) );
	if ( this->KeyBindComponent == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "ACSR_Player_May : this->KeyBindComponent is null" ) );
	}
	this->HammerLocation = CreateDefaultSubobject<USceneComponent> ( TEXT ( "HammerLocation" ) );
	if ( this->HammerLocation == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "ACSR_Player_May : this->HammerLocation is null" ) );
	}
	this->HammerLocation->SetupAttachment(RootComponent);

	this->HammerLocation->SetRelativeLocation(FVector(-70.0f, 0.0f, 0.0f));

	ConstructorHelpers::FClassFinder<UCSR_MayAnimation> TempEnemyAnim ( TEXT ( "/Script/Engine.AnimBlueprint'/Game/CSR/Animation/animation/ABS_MayAnimation.ABS_MayAnimation'" ) );
	if ( TempEnemyAnim.Succeeded ( ) ) {
		GetMesh ( )->SetAnimInstanceClass ( TempEnemyAnim.Class );
	}
}

void ACSR_Player_May::BeginPlay ( )
{
	Super::BeginPlay ( );
	this->MakeEnhancedInputLocalSubSystem ( );
	
	FString testString = FString::Printf ( TEXT ( "%f, %f, %f" ) , HammerPlayerSocketLotation.X , HammerPlayerSocketLotation.Y , HammerPlayerSocketLotation.Z );
	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , testString );
	this->MayUI = Cast<UCSR_PlayerWidget> ( CreateWidget ( this->GetWorld ( ) , this->PlayerHPWidget ) );
	this->MayUI->AddToViewport ( );
	this->MayUI->InitHP ( this->MaxHp );
}

// PlayerController를 IMC_PlayerController와 맵핑.

void ACSR_Player_May::MakeEnhancedInputLocalSubSystem ( )
{
	// 해당 Mannger의 컨트롤러가 존재하는지 확인합니다.
	APlayerController* Player_1 = UGameplayStatics::GetPlayerController ( this->GetWorld ( ) , 0 );
	if ( Player_1 == nullptr ) {
		UCSR_FunctionLib::ExitGame ( GetWorld ( ) , FString ( "Player_1 is null" ) );
	}

	// EnhancedInput을 연결합니다.
	UEnhancedInputLocalPlayerSubsystem* SubSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem> ( Player_1->GetLocalPlayer ( ) );
	if ( SubSys == nullptr ) {
		UCSR_FunctionLib::ExitGame ( GetWorld ( ) , FString ( "SubSyn is null" ) );
	}
	// EnhancedInput을 IMC_...를 맵핑합니다.
	SubSys->AddMappingContext ( this->IMC_PlayerController_ , 0 );
	this->PlayerIndex = 0;

}


void ACSR_Player_May::ChangeCharacterColor_Implementation ( )
{
	
}

void ACSR_Player_May::TranceSIn()
{
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, this->PlayerIndex);
	if (CameraManager)
	{
		CameraManager->StartCameraFade(0.0f, 1.0f, 0.5f, FLinearColor::Black, false, true);
	}
}

void ACSR_Player_May::LightOn()
{
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, this->PlayerIndex);
	if (CameraManager)
	{
		CameraManager->StartCameraFade(1.0f, 0.0f, 0.5f, FLinearColor::Black, false, true);
	}
}

void ACSR_Player_May::Tick ( float DeltaTime )
{
	Super::Tick ( DeltaTime );

	if ( ((this->UseHammerComp->Hammer->bMoveToNail == false) && (this->UseHammerComp->Hammer->bIsHanging == true)) || (this->UseHammerComp->Hammer->bMoveToNail == true) )
	{
		HammerPlayerSocketLotation = this->UseHammerComp->Hammer->MeshComp->GetSocketLocation ( TEXT ( "PlayerAttachingPoint" ) );
		SetActorLocation ( HammerPlayerSocketLotation );
	}
	if ( this->flag1 ) {
		this->ChangeCharacterColor ( );
		this->ItTakesMap->SetMayDie(true);
		this->MayUI->TakeDamageEvent ( this->CurHp , this->MaxHp );
		this->flag1 = false;
	}
	//if (this->flag2 )
}

void ACSR_Player_May::SetupPlayerInputComponent ( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent ( PlayerInputComponent );
#pragma region
	UEnhancedInputComponent* InputKey = CastChecked<UEnhancedInputComponent> ( PlayerInputComponent );
	if ( InputKey == nullptr ) {
		UCSR_FunctionLib::ExitGame ( GetWorld ( ) , FString ( "ACSR_Player_May : InputKey is null" ) );
	}

	this->KeyBindComponent->SetupInputComponent( InputKey );
#pragma endregion EnhancedInput register

	Setting ( );
}


