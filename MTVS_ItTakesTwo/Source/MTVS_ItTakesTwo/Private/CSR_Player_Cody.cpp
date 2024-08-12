// Fill out your copyright notice in the Description page of Project Settings.


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
#include "CSR_CodyAnimation.h"
#include "GameFramework/CharacterMovementComponent.h"

ACSR_Player_Cody::ACSR_Player_Cody ( )
{
	this->CodyPileComp = CreateDefaultSubobject< UCSR_CodyPile> ( TEXT ( "CodyPileComp" ) );
	if ( this->CodyPileComp == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "ACSR_Player_Cody : this->CodyPileComp is null" ) );
	}
	this->CodyPileComp->InitComp ( this->CameraComp , this->SpringArmComp , this->SpringArmComp->TargetArmLength , this );

	this->ArrowComp = CreateDefaultSubobject<UArrowComponent> ( TEXT ( "ArrowComp" ) );
	if ( this->ArrowComp == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "ACSR_Player_Cody : this->ArrowComp is null" ) );
	}
	this->ArrowComp->SetupAttachment ( RootComponent );
	this->ArrowComp->SetRelativeLocation ( FVector ( 0 , 70.0f , 70.0f ) );
	this->KeyBindComponent = CreateDefaultSubobject<UCSR_C_AComp_InputBIndCody> ( TEXT ( "KeyBindComponent" ) );
	ConstructorHelpers::FClassFinder<UCSR_CodyAnimation> TempEnemyAnim ( TEXT ( "/Script/Engine.AnimBlueprint'/Game/CSR/Animation/animation/ABS_CodyAnimation.ABS_CodyAnimation_C'" ) );
	if ( TempEnemyAnim.Succeeded ( ) ) {
		GetMesh ( )->SetAnimInstanceClass ( TempEnemyAnim.Class );
	}
	this->AnimCody = Cast<UCSR_CodyAnimation> ( GetMesh ( )->GetAnimInstance ( ) );

	this->NailBagLocation = CreateDefaultSubobject<USceneComponent> ( TEXT ( "NailBahLocation" ) );
	if ( this->NailBagLocation == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "ACSR_Player_May : this->NailBagLocation is null" ) );
	}
	this->NailBagLocation->SetupAttachment ( RootComponent );
	this->NailBagLocation->SetRelativeLocationAndRotation ( FVector ( -50.0f , 0.0f , 20.0f ) , FRotator (  -20.0f , 90.0f, 0.0f ) );

	this->GetCharacterMovement ( )->bOrientRotationToMovement = true;
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

