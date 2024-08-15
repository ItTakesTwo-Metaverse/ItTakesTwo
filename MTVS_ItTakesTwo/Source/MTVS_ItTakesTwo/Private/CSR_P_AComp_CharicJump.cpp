// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_P_AComp_CharicJump.h"
#include "CSR_P_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CSR_FunctionLib.h"
#include "CSR_P_AComp_CharicStateMannage.h"
#include "CSR_P_AComp_CharicMovement.h"

// Sets default values for this component's properties
UCSR_P_AComp_CharicJump::UCSR_P_AComp_CharicJump()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCSR_P_AComp_CharicJump::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	this->Character_ = Cast<ACSR_P_Player> ( this->GetOwner ( ) );
	if ( this->Character_ == nullptr ) {
		UCSR_FunctionLib::ExitGame(this->GetWorld(), FString("UCSR_P_AComp_CharicJump : this->Character_ is null" ));
	}
	this->CharacterStateComp = this->Character_->CharacterStateComp;
	if ( this->CharacterStateComp == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_P_AComp_CharicJump : this->CharacterStateComp is null" ) );
	}
	Setting( );
}


// Called every frame
void UCSR_P_AComp_CharicJump::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// 초기값을 init
void UCSR_P_AComp_CharicJump::Setting ( )
{
	this->CharacterStateComp->JumpZVelocity = this->FirstJumpZVelocity;
	this->Character_->JumpMaxHoldTime = JumpMaxHoldT;
	this->Character_->JumpMaxCount = 10;
}

// input 점프가 들어오면 발생하는 함수
void UCSR_P_AComp_CharicJump::PlayerJump ( const FInputActionValue& Value )
{
	if ( this->Character_->CharacterStateMannageComp->AddState ( JUMP ) ) {
		UE_LOG ( LogTemp , Warning , TEXT ( "Jump" ) );
		if ( this->CharacterStateComp->IsFalling ( ) == true ) {
			UE_LOG ( LogTemp , Warning , TEXT ( "%d" ) , this->SecondJumpPossible );
			if ( this->SecondJumpPossible == false ) {
				return;
			}
			this->Character_->SecondJumpToOtherComp();
			this->Character_->Jump ( );
			this->SecondJumpPossible = false;
		}
		else {
			this->Character_->Jump ( );
		}
	}
}

void UCSR_P_AComp_CharicJump::Landed ( )
{
	this->SecondJumpPossible = true;
	UE_LOG(LogTemp, Warning, TEXT("123" ));
	this->Character_->CharacterStateMannageComp->RemoveState(JUMP);
	this->Character_->CharacterStateMannageComp->RemoveState ( JUMPMOVE );
}
