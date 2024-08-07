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
	bIsAttacking = false;
	bIsPausing = false;
}

void URightArmAnimInstance::NativeUpdateAnimation ( float DeltaSeconds )
{
	Super::NativeUpdateAnimation ( DeltaSeconds );

    switch ( AnimState )
    {
    case ERightArmAnimState::Start:
        bIsAttacking = false;
        bIsPausing = false;
        //GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Magenta , TEXT ( "Right Arm Anim : Start" ) );
        //UE_LOG ( LogTemp , Warning , TEXT ( "Right Arm Anim : Start" ) );
        break;

    case ERightArmAnimState::Idle:
        bIsAttacking = false;
        bIsPausing = false;
        //GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Magenta , TEXT ( "Right Arm Anim : Idle" ) );
        //UE_LOG ( LogTemp , Warning , TEXT ( "Right Arm Anim : Idle" ) );
        break;

    case ERightArmAnimState::CoolDown:
        bIsAttacking = false;
        bIsPausing = false;
        break;
 
    case ERightArmAnimState::Attack1:
                //GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Magenta , TEXT ( "Right Arm Anim : Attack1" ) );
                //UE_LOG ( LogTemp , Warning , TEXT ( "Right Arm Anim : Attack1" ) );
                bIsAttacking = true;
        break;

    case ERightArmAnimState::Paused:
            bIsPausing = true;
        break;

    case ERightArmAnimState::DestroyRightArm:
        break;

    case ERightArmAnimState::Attack2:
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
