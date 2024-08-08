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
}

void URightArmAnimInstance::NativeUpdateAnimation ( float DeltaSeconds )
{
	Super::NativeUpdateAnimation ( DeltaSeconds );

    switch ( AnimState )
    {
    case ERightArmAnimState::Start:
            bIsAttacking1 = false;
            bIsPausing = false;
            bIsAttacking2 = false;
        break;

    case ERightArmAnimState::Idle:
            bIsAttacking1 = false;
            bIsPausing = false;
            bIsAttacking2 = false;
        break;

    case ERightArmAnimState::CoolDown:
            bIsAttacking1 = false;
            bIsPausing = false;
            bIsAttacking2 = false;
        break;
 
    case ERightArmAnimState::Attack1:
            bIsAttacking1 = true;
        break;

    case ERightArmAnimState::Paused:
            bIsPausing = true;
        break;

    case ERightArmAnimState::DestroyRightArm:
        break;

    case ERightArmAnimState::Attack2Drill:
        bIsAttacking2 = false;
        break;

    case ERightArmAnimState::Attack3:
        break;

    case ERightArmAnimState::Attack4:
        break;

    case ERightArmAnimState::Attack5:
        break;

    default:
        break;
    }
}

void URightArmAnimInstance::SetAnimState ( ERightArmAnimState NewState )
{
    AnimState = NewState;
}
