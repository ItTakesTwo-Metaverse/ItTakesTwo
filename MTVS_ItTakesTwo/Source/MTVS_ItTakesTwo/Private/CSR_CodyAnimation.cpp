// Fill out your copyright notice in the Description page of Project Settings.

#include "CSR_CodyAnimation.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CSR_FunctionLib.h"
#include "CSR_Player_Cody.h"
#include "GameFramework/Character.h"
#include "GameFramework/MovementComponent.h"
#include "Kismet/GameplayStatics.h"

void UCSR_CodyAnimation::NativeInitializeAnimation ( )
{
	Super::NativeInitializeAnimation ( );
	this->Player = Cast<ACSR_Player_Cody> ( TryGetPawnOwner ( ) );
}

void UCSR_CodyAnimation::NativeUpdateAnimation ( float DeltaSeconds )
{
	Super::NativeUpdateAnimation( DeltaSeconds );
	if ( this->Player == nullptr ) {
		return ;
	}
	
	FVector velocity = Player->GetCharacterMovement ( )->Velocity;
	FVector forwardVector = Player->GetActorForwardVector ( );

	this->Speed = FVector::DotProduct ( forwardVector , velocity );

	FVector rightVector = Player->GetActorRightVector ( );

	//// 좌, 우 속도
	this->Direction = FVector::DotProduct ( rightVector , velocity );
}

