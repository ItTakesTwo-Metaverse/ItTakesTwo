// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_P_Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"
#include "CSR_Direction_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "CSR_FunctionLib.h"
#include "GameFramework/NavMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CSR_P_AComp_CharicStateMannage.h"
#include "CSR_P_AComp_CharicMovement.h"
#include "CSR_P_AComp_InputBInd.h"
#include "CSR_P_AComp_CharicJump.h"

// Sets default values
ACSR_P_Player::ACSR_P_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스프링암을 생성해서
	this->SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	if ( this->SpringArmComp == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "ACSR_P_Player : this->SpringArmComp is null" ) );
	}
	// 루트에 붙이고 싶다.
	this->SpringArmComp->SetupAttachment(RootComponent);
	// 스프링 암의 상대 좌표를 (x = 0, y = 40, Z = 80) 
	this->SpringArmComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	// TargetArmLength : 1000.0f
	this->SpringArmComp->TargetArmLength = EarlyCameraDistance;


	this->SpringArmComp->bUsePawnControlRotation = true;

	// 카메라를 생성하고 싶다.
	this->CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	if ( this->CameraComp == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "ACSR_P_Player : this->CameraComp is null" ) );
	}
	// 스프링 암을 붙이고 싶다.
	this->CameraComp->SetupAttachment(this->SpringArmComp);

	this->CameraComp->bUsePawnControlRotation = false;

	this->bUseControllerRotationYaw = false;
	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationRoll = false;

	this->CharacterStateComp = this->GetCharacterMovement ( );
	this->CharacterStateMannageComp = CreateDefaultSubobject< UCSR_P_AComp_CharicStateMannage> ( TEXT ( "CharacterStateMannageComp" ) );
	this->CharicMovementComp = CreateDefaultSubobject<UCSR_P_AComp_CharicMovement> (TEXT("CahricMovementComp" ) );
	this->CameraMomveComp = CreateDefaultSubobject<UCSR_P_AComp_CameraMove> ( TEXT ( "CameraMomveComp" ) );
	//this->KeyBindComponent = CreateDefaultSubobject<UCSR_P_AComp_InputBInd> ( TEXT ( "KeyBindComponent" ) );
	this->CharicJumpComp = CreateDefaultSubobject<UCSR_P_AComp_CharicJump> ( TEXT ( "CharicJumpComp" ) );
	if ( !(this->CharacterStateComp && this->CharacterStateMannageComp && this->CharicMovementComp && this->CameraMomveComp && this->CharicJumpComp) ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "ACSR_P_Player : component is null" ) );
	}
}

// Called when the game starts or when spawned
void ACSR_P_Player::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACSR_P_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Called to bind functionality to input
void ACSR_P_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACSR_P_Player::Setting ( )
{
	this->AddControllerPitchInput ( this->EarlyCameraArmRotateHeight );
	this->SpringArmComp->TargetArmLength = EarlyCameraDistance;
}

void ACSR_P_Player::Landed ( const FHitResult& Hit )
{
	Super::Landed(Hit);

	this->CharicJumpComp->Landed();
}

void ACSR_P_Player::OnDamaged ( int32 Damage )
{
	if ( this->CurHp - Damage <= 0 ) {
		this->CurHp = 0;
	}
	else {
		this->CurHp = this->CurHp - Damage;
		UE_LOG(LogTemp, Warning, TEXT("HP : %d" ), this->CurHp);
	}
}

void ACSR_P_Player::SecondJumpToOtherComp ( )
{
	this->CharicMovementComp->InitSecondJump ();
}
