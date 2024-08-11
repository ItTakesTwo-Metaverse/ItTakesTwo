// Fill out your copyright notice in the Description page of Project Settings.


#include "RightArmAnimInstance.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"

URightArmAnimInstance::URightArmAnimInstance ( )
	: AnimState ( ERightArmAnimState::Start )
{}


void URightArmAnimInstance::NativeInitializeAnimation ( )
{
	Super::NativeInitializeAnimation ( );
	bIsAttacking1 = false;
	bIsPausing = false;
    bIsAttacking2 = false;
    bIsAttacking3 = false;
}

void URightArmAnimInstance::NativeUpdateAnimation ( float DeltaSeconds )
{
	Super::NativeUpdateAnimation ( DeltaSeconds );

    switch ( AnimState )
    {
    case ERightArmAnimState::Start:
        break;

    case ERightArmAnimState::Idle:
            bIsAttacking1 = false;
            bIsPausing = false;
            bIsAttacking2 = false;
            bIsAttacking3 = false;
        break;

    case ERightArmAnimState::CoolDown:
        break;
 
    case ERightArmAnimState::Attack1:
		    bIsAttacking1 = true;
		    bIsPausing = false;
		    bIsAttacking2 = false;
		    bIsAttacking3 = false;
        break;

    case ERightArmAnimState::Paused:
            bIsAttacking1 = true;
            bIsPausing = true;
            bIsAttacking3 = false;
        break;

    case ERightArmAnimState::Attack2:
            bIsAttacking2 = true;
        break;

    case ERightArmAnimState::Attack3:
            bIsAttacking3 = true;
			bIsAttacking1 = false;
        break;

    case ERightArmAnimState::Attack4:
        break;

    case ERightArmAnimState::Attack5:
        break;

    case ERightArmAnimState::Die:
        break;

    default:
        break;
    }
}

void URightArmAnimInstance::SetAnimState ( ERightArmAnimState NewState )
{
    AnimState = NewState;
}

