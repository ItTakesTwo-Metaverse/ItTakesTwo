// Fill out your copyright notice in the Description page of Project Settings.


//#include "RightArmAnim.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

URightArmAnim::URightArmAnim ( )
	: AnimState ( ERightAnimState::Start )
{}

void URightArmAnim::NativeInitializeAnimation ( )
{
    Super::NativeInitializeAnimation ( );
    bIsAttacking = false;
    bIsPausing = false;
}

void URightArmAnim::NativeUpdateAnimation ( float DeltaSeconds )
{
    Super::NativeUpdateAnimation ( DeltaSeconds );

    switch ( AnimState )
    {
    case ERightAnimState::Start:
        bIsAttacking = false;
        bIsPausing = false;
        //GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Magenta , TEXT ( "Right Arm Anim : Start" ) );
        //UE_LOG ( LogTemp , Warning , TEXT ( "Right Arm Anim : Start" ) );
        break;
    case ERightAnimState::Idle:
        bIsAttacking = false;
        bIsPausing = false;
        //GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Magenta , TEXT ( "Right Arm Anim : Idle" ) );
        //UE_LOG ( LogTemp , Warning , TEXT ( "Right Arm Anim : Idle" ) );
        break;
    case ERightAnimState::Paused:

        if ( !bIsPausing )
        {
            if ( PausedMotage )
            {
                Montage_Play ( PausedMotage );
                bIsPausing = true;
            }
        }
        

        break;
    case ERightAnimState::Attack1:
        
        if ( !bIsAttacking )
        {   
            
            if ( Attack1Montage )
            {
                GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Magenta , TEXT ( "Right Arm Anim : Attack1" ) );
                UE_LOG ( LogTemp , Warning , TEXT ( "Right Arm Anim : Attack1" ) );
                MontageEndedDelegate.BindUObject ( this , &URightArmAnim::OnAttackMontageEnded );
                Montage_Play ( Attack1Montage );
                Montage_SetEndDelegate ( MontageEndedDelegate , Attack1Montage );
                bIsAttacking = true;
            }
        }
        break;
    case ERightAnimState::Attack2:
        break;
    case ERightAnimState::Attack3:
        break;
    case ERightAnimState::Attack4:
        break;
    case ERightAnimState::Attack5:
        break;
    case ERightAnimState::CoolDown:
        bIsAttacking = false;
        bIsPausing = false;
        break;
    case ERightAnimState::DestroyRightArm:
        break;
    default:
        break;
    }

}

void URightArmAnim::SetAnimState ( ERightAnimState NewState )
{
    AnimState = NewState;
}

void URightArmAnim::OnAttackMontageEnded ( UAnimMontage* Montage , bool bInterrupted )
{
	if ( Montage == Attack1Montage )
	{
		bIsAttacking = false;
	}
}

