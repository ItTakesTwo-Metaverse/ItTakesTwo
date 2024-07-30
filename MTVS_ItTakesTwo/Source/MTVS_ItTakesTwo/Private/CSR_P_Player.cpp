// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_P_Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACSR_P_Player::ACSR_P_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스프링암을 생성해서
	this->SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	// 루트에 붙이고 싶다.
	this->SpringArmComp->SetupAttachment(RootComponent);
	// 스프링 암의 상대 좌표를 (x = 0, y = 40, Z = 80) 
	this->SpringArmComp->SetRelativeLocation(FVector(0.0f, 40.0f, 80.0f));
	// TargetArmLength : 200.0f
	this->SpringArmComp->TargetArmLength = 200.0f;

	// 카메라를 생성하고 싶다.
	this->CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	// 스프링 암을 붙이고 싶다.
	this->CameraComp->SetupAttachment(this->SpringArmComp);

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
	FTransform See = FTransform(this->GetControlRotation());
	this->Direction = See.TransformVector(this->Direction);
	this->AddMovementInput(this->Direction, 1);
	this->Direction = FVector::ZeroVector;
}

//Called to bind functionality to input
void ACSR_P_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACSR_P_Player::Player_Move(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Click"));
	FVector2D V = Value.Get<FVector2D>();
	this->Direction.X = V.X;
	this->Direction.Y = V.Y;
	this->Direction.Normalize();
}

