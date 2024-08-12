// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_MayAnimation.h"
#include "CSR_FunctionLib.h"
#include "CSR_Player_May.h"
#include "CSR_P_Player.h"
#include "CSR_P_AComp_CharicStateMannage.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CSR_MayUseHammerObj.h"
#include "GameFramework/Actor.h"
#include "HSW_Hammer.h"

void UCSR_MayAnimation::NativeInitializeAnimation ( )
{
	Super::NativeInitializeAnimation ( );
	this->Player = Cast<ACSR_Player_May> ( TryGetPawnOwner ( ) );
	if ( this->Player == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_CodyAnimation : this->Player is null" ) );
		return;
	}
	this->Player->AnimMay = this;
	this->Player->CharacterStateMannageComp->Anim = this;
}

void UCSR_MayAnimation::NativeUpdateAnimation ( float DeltaSeconds )
{
	Super::NativeUpdateAnimation ( DeltaSeconds );
	if ( this->Player == nullptr ) {
		return;
	}

	FVector velocity = Player->GetCharacterMovement ( )->Velocity;
	FVector forwardVector = Player->GetActorForwardVector ( );

	this->Speed = FVector::DotProduct ( forwardVector , velocity );

	FVector rightVector = Player->GetActorRightVector ( );

	//// 좌, 우 속도
	this->Direction = FVector::DotProduct ( rightVector , velocity );
}

void UCSR_MayAnimation::AnimNotify_HammerAttach ( )
{
	//this->Player->UseHammerComp->Hammer->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform );
	//if (this->Player->GetMesh()->DoesSocketExist( FName ( "hammerL" ) ) == true)
	//	UCSR_FunctionLib::PrintWindow(TEXT("heelo" ));
	this->Player->UseHammerComp->Hammer->AttachToComponent (Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hammerL" ));
	
	//this->Player->UseHammerComp->Hammer->SetActorRelativeRotation ( FRotator ( 0.0f , 90.0f , 0.0f ) );
}

void UCSR_MayAnimation::AnimNotify_HammerDetach ( )
{
	this->Player->UseHammerComp->Hammer->AttachToComponent (Player->HammerLocation , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
	this->Player->UseHammerComp->Hammer->SetActorRelativeRotation ( FRotator ( 0.0f , 90.0f , 0.0f ) );
}

void UCSR_MayAnimation::AnimNotify_AttackStart ( )
{
	
}

void UCSR_MayAnimation::AnimNotify_AttackEnd ( )
{
	this->Player->CharacterStateMannageComp->RemoveState(ATTACK);
}

void UCSR_MayAnimation::PlayerAttackMontage ( )
{
	Montage_Play(this->AttackMontage);
}
