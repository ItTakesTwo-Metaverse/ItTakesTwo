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
	this->SpringArmComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	// TargetArmLength : 1000.0f
	this->SpringArmComp->TargetArmLength = EarlyCameraDistance;


	this->SpringArmComp->bUsePawnControlRotation = true;

	// 카메라를 생성하고 싶다.
	this->CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	// 스프링 암을 붙이고 싶다.
	this->CameraComp->SetupAttachment(this->SpringArmComp);

	this->CameraComp->bUsePawnControlRotation = false;

	this->bUseControllerRotationYaw = false;
	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationRoll = false;

	this->CharacterStateMannageComp = CreateDefaultSubobject< UCSR_P_AComp_CharicStateMannage> ( TEXT ( "CharacterStateMannageComp" ) );
	//GetCharacterMovement()->bOrientRotationToMovement = true;
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

	// 카메라 정면 벡터에 맞는 플레이어의 회전값을 구한다.
	//FRotator NewRot = UKismetMathLibrary::MakeRotFromX ( this->ChoosedDirection );
	//// 플레이어에게 해당 회전값을 적용시킨다.
	//SetActorRotation(NewRot);
	// 풀래이어는 앞으로 이동한다.
	this->AddMovementInput( this->ChoosedDirection , (this->AbsScale));
	this->AbsScale = 0.0f;
	
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
	this->CharacterMoveMentComp = this->GetCharacterMovement ( );
	CharacterMoveMentComp->MaxWalkSpeed = this->Speed;
	CharacterMoveMentComp->JumpZVelocity = this->FirstJumpZVelocity;
	this->JumpMaxHoldTime = JumpMaxHoldT;
}

void ACSR_P_Player::Player_Move(const FInputActionValue& Value)
{
	FVector2D V = Value.Get<FVector2D> ();
	// TargetValue는 입력 키 X, Y 의 절대값 value를 더하여 이동량을 결정한다.
	float TargetValue = UCSR_FunctionLib::SelectABSUpperFloat( V.X , V.Y );
	// TagetValue에 따라 캐릭터 이동속도의 곱하기 상수를 결정합니다.
	if ( TargetValue < this->StickSensitivity_NoInput ) {
		return;
	}
	else if ( TargetValue < this->StickSensitivity_WeakInput ) {
		this->AbsScale = 0.5;
	}
	else {
		this->AbsScale = 1.0f;
	}
	// X,Y키가 8방향 중 어느곳에 더 가까운지를 체크합니다.
	this->PadDirection.X = V.Y;
	this->PadDirection.Y = V.X;
	this->PadDirection.Normalize();
	int32 Flag = ChooseDirectionFlag ( this->PadDirection );
	// 카메라가 정면이 플레이어의 정면 벡터라고보고 플레이어의 이동벡터를 결정합니다.
	CaracterDirection ( Flag );
	this->PadDirection.X = 0.0f;
	this->PadDirection.Y = 0.0f;
}

// 패드의 방향이 8방향 중 어느곳에 더 가까운지를 판단합니다.
int32 ACSR_P_Player::ChooseDirectionFlag ( FVector2D& PadDirection_ ) {
	// 전역 게임 인스텐스에서 8방향 배열을 가져옵니다.
	UCSR_Direction_GameInstance *GameInstance = Cast< UCSR_Direction_GameInstance>(UGameplayStatics::GetGameInstance(this->GetWorld()));

	const TArray<FVector2D> &Directions = GameInstance->Directions;
	float RelativeDValue = -1;
	int32 flag = 0;
	int32 answer = 0;
	for ( FVector2D param : Directions ) {
		flag = flag + 1;
		float CalcDot = FVector2D::DotProduct(PadDirection_, param);
		if ( CalcDot > RelativeDValue ) {
			answer = flag;
			RelativeDValue = CalcDot;
		}
	}
	return (answer);
}

// 카메라 정면이 플레이어의 정면으로치고 플레이어의 이동방향을 결정합니다.
void ACSR_P_Player::CaracterDirection ( int32 flag )
{
	UCSR_Direction_GameInstance* GameInstance = Cast< UCSR_Direction_GameInstance> ( UGameplayStatics::GetGameInstance ( this->GetWorld ( ) ) );
	const TArray<FVector2D>& Directions = GameInstance->Directions;
	FVector CameraF = this->CameraComp->GetForwardVector ( );
	FVector CameraR = this->CameraComp->GetRightVector ( );
	//UE_LOG(LogTemp, Warning, TEXT("%f" ), this->a);
	CameraF.Z = 0;
	CameraR.Z = 0;
	this->ChoosedDirection = ((CameraF * Directions[flag - 1].X + CameraR * Directions[flag - 1].Y) / 2).GetUnsafeNormal();
}


// 점프 기능은 추후 수정 요망
void ACSR_P_Player::PlayerJump ( const FInputActionValue& Value )
{
	UE_LOG ( LogTemp , Warning , TEXT ( "Jump" ));
	if ( this->CharacterMoveMentComp->IsFalling ( ) == true ) {
		UE_LOG ( LogTemp , Warning , TEXT ( "%d" ) , this->SecondJumpPossible );
		if ( this->SecondJumpPossible == false ) {
			return;
		}
		LaunchCharacter ( FVector ( 0 , 0 ,	this->SecondJumpZVelocity ) , false , true );
		this->SecondJumpPossible = false;
	}
	else {
		this->Jump ( );
	}
}

void ACSR_P_Player::Landed ( const FHitResult& Hit )
{
	Super::Landed(Hit);

	this->SecondJumpPossible = true;
}

// 마우스, 패드 오른쪽 스틱의 입력값에 따라 플레이어 컨트롤(즉 시야 회전)을 시켜줍니다.
void ACSR_P_Player::Player_View ( const FInputActionValue& Value )
{	
	//this->CameraComp
	FVector2D V = Value.Get<FVector2D>();
	//this->CameraComp->
	AddControllerYawInput(-V.X);
	V.X = 0;
	AddControllerPitchInput(V.Y);	
	V.Y = 0;
}

