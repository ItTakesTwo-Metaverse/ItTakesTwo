// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_P_AComp_CharicMovement.h"
#include "CSR_P_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CSR_FunctionLib.h"
#include "Kismet/KismetMathLibrary.h"
#include "CSR_P_AComp_CharicStateMannage.h"
#include "CSR_Direction_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UCSR_P_AComp_CharicMovement::UCSR_P_AComp_CharicMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCSR_P_AComp_CharicMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	this->Character_ = Cast<ACSR_P_Player> ( this->GetOwner ( ) );
	if ( this->Character_ == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_P_AComp_CharicMovement : this->Character_ is null" ) );
	}
	this->CharacterStateComp = this->Character_->CharacterStateComp;
	if ( this->CharacterStateComp == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_P_AComp_CharicMovement : this->CharacterStateComp is null" ) );
	}
	this->Setting ();
}


// Called every frame
void UCSR_P_AComp_CharicMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	switch ( this->MoveFlag )
	{
	case DONTMOVE:
		//UE_LOG ( LogTemp , Warning , TEXT ( "DONTMOVE!!!" ) );
		break;
	case NORMALEMOVE:
		//UE_LOG ( LogTemp , Warning , TEXT ( "NORMALEMOVE" ) );
		//UE_LOG ( LogTemp , Warning , TEXT ( "chose Di %f %f" ) , this->ChoosedDirection.X , this->ChoosedDirection.Y );
		//UE_LOG ( LogTemp , Warning , TEXT ( "abc : %f" ) , this->AbsScale );
		this->MoveFlag = DONTMOVE;
		this->Character_->CharacterStateMannageComp->RemoveState(MOVE);
		this->Character_->AddMovementInput ( this->ChoosedDirection , (this->AbsScale) );
		this->ChoosedDirection = FVector::ZeroVector;
		this->AbsScale = 0.0f;
		break;
	case JUMPMOVEE:
		//UE_LOG ( LogTemp , Warning , TEXT ( "JUMPMOVEE" ) );
		if ( this->SecondJump == true ) {
			// 2단 점프 시 이동 키 입력되어 있으면 새로운 이동 방향을 입력받는다.
			// 그게 아니면 원래 이동거리로 간다.
			if ( this->ChoosedDirection.X != 0 || this->ChoosedDirection.Y != 0 ) {
				this->CharacterStateComp->Velocity.X = 600 * this->ChoosedDirection.X;
				this->CharacterStateComp->Velocity.Y = 600 * this->ChoosedDirection.Y;
			}
			this->SecondJump = false;
		}
		// 키를 입력 받지 않는다면 가속도가 줄어들지 않는다.
		if ( !(this->ChoosedDirection.X == 0.0f && this->ChoosedDirection.Y == 0.0f) ) {
			this->Acceleration = this->Acceleration + DeltaTime * 20;
		}

		// 감속 치입니다.
		FVector DesVec = FVector(this->Acceleration * this->ChoosedDirection.X, this->Acceleration * this->ChoosedDirection.Y, 0.0f);
		// 감속 치를 더한 이동속도
		FVector Vec = (FVector( this->CharacterStateComp->Velocity.X, this->CharacterStateComp->Velocity.Y, 0.0f ) + DesVec).GetClampedToMaxSize ( 600.0f );
		Vec.Z =  this->CharacterStateComp->Velocity.Z;
		//UE_LOG ( LogTemp , Warning , TEXT ( "chose Di %f %f %f" ) , this->CharacterStateComp->Velocity.X , this->CharacterStateComp->Velocity.Y , this->CharacterStateComp->Velocity.Z);

		// 해당 이동속도를 캐릭터에 적용.
		this->CharacterStateComp->Velocity = Vec;
		this->ChoosedDirection = FVector::ZeroVector;
		break;
	}
}

void UCSR_P_AComp_CharicMovement::Setting ( )
{
	this->CharacterStateComp = this->Character_->GetCharacterMovement ();
	this->CharacterStateComp->MaxWalkSpeed = this->Speed;
}

void UCSR_P_AComp_CharicMovement::PlayerMoveSelect ( const FInputActionValue& Value )
{
	FVector2D V = Value.Get<FVector2D> ( );
	// TargetValue는 입력 키 X, Y 의 절대값 value를 더하여 이동량을 결정한다.
	float TargetValue = UCSR_FunctionLib::SelectABSUpperFloat ( V.X , V.Y );
	//UE_LOG(LogTemp, Warning, TEXT("%f %f" ), V.X , V.Y);

	// TagetValue의 크기에 따라 이동속도를 결정한다.
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
	this->PadDirection.Normalize ( );
	int32 Flag = ChooseDirectionFlag ( this->PadDirection );

	// 카메라가 정면이 플레이어의 정면 벡터라고보고 플레이어의 이동벡터를 결정합니다.
	CaracterDirection ( Flag );
	FRotator NewRot = UKismetMathLibrary::MakeRotFromX ( this->ChoosedDirection );
	this->Character_->SetActorRotation ( NewRot );

	this->PadDirection.X = 0.0f;
	this->PadDirection.Y = 0.0f;
	// 현재 캐릭터의 상태에 따라 다른 이동방식이 적용됩니다.

	if ( this->Character_->CharacterStateMannageComp->CurrentState  && this->Character_->CharacterStateMannageComp->AddState ( JUMPMOVE ))
	{
		this->MoveFlag = JUMPMOVEE;
	}
	else if ( this->Character_->CharacterStateMannageComp->AddState ( MOVE ) )
	{
		this->Acceleration = 0;
		this->MoveFlag = NORMALEMOVE;
	}
}

// 패드의 방향이 8방향 중 어느곳에 더 가까운지를 판단합니다.
int32 UCSR_P_AComp_CharicMovement::ChooseDirectionFlag ( FVector2D& PadDirection_ ) {
	// 전역 게임 인스텐스에서 8방향 배열을 가져옵니다.
	UCSR_Direction_GameInstance* GameInstance = Cast< UCSR_Direction_GameInstance> ( UGameplayStatics::GetGameInstance ( this->GetWorld ( ) ) );

	const TArray<FVector2D>& Directions = GameInstance->Directions;
	float RelativeDValue = -1;
	int32 flag = 0;
	int32 answer = 0;
	for ( FVector2D param : Directions ) {
		flag = flag + 1;
		float CalcDot = FVector2D::DotProduct ( PadDirection_ , param );
		if ( CalcDot > RelativeDValue ) {
			answer = flag;
			RelativeDValue = CalcDot;
		}
	}
	return (answer);
}

// 카메라 정면이 플레이어의 정면으로치고 플레이어의 이동방향을 결정합니다.
void UCSR_P_AComp_CharicMovement::CaracterDirection ( int32 flag )
{
	UCSR_Direction_GameInstance* GameInstance = Cast< UCSR_Direction_GameInstance> ( UGameplayStatics::GetGameInstance ( this->GetWorld ( ) ) );
	const TArray<FVector2D>& Directions = GameInstance->Directions;
	FVector CameraF = this->Character_->CameraComp->GetForwardVector ( );
	FVector CameraR = this->Character_->CameraComp->GetRightVector ( );
	CameraF.Z = 0;
	CameraR.Z = 0;
	this->ChoosedDirection = ((CameraF * Directions[flag - 1].X + CameraR * Directions[flag - 1].Y) / 2).GetUnsafeNormal ( );
}

void UCSR_P_AComp_CharicMovement::InitSecondJump ( )
{
	this->SecondJump = true;
	this->Acceleration = 0;
}

void UCSR_P_AComp_CharicMovement::RunStart ( const FInputActionValue& Value )
{
	if ( this->Character_->CharacterStateMannageComp->AddState ( RUN ) )
	{
		this->CharacterStateComp->MaxWalkSpeed = 1000;
	}
}

void UCSR_P_AComp_CharicMovement::RunEnd ( const FInputActionValue& Value )
{
	this->Character_->CharacterStateMannageComp->RemoveState ( RUN );
	this->CharacterStateComp->MaxWalkSpeed = 600;
}

