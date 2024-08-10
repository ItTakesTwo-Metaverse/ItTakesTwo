﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBoxBossFSM.h"
#include "../ToolboxBoss.h"
#include "HSW_Player.h"
#include "GameFramework/Character.h"
#include "RightArmAnimInstance.h"

// Sets default values for this component's properties
UToolBoxBossFSM::UToolBoxBossFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AttackCoolDown = 3;
	AttackTimer = 0;
	Attack1Duration = 20; // Attack1 : 팔 휘두르기 공격 시간 (애님8초+대기4) 12초 / 테스트용 20초
	Attack2Duration = 20; // Attack2 : 전동드릴 바닥 뚫는 공격 시간
	Attack3Duration = 13; // Attack3 : 전동드릴 회전 공격 시간
}


// Called when the game starts
void UToolBoxBossFSM::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AToolboxBoss>(GetOwner());
	player = Cast<ACharacter> ( GetWorld ( )->GetFirstPlayerController ( )->GetCharacter ( ) );

	// 초기 상태를 Start로 설정
	ChangeState(EBossState::Start );
}


// Called every frame
void UToolBoxBossFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 실행창에 상태 메세지 출력
	FString logMsg = UEnum::GetValueAsString(CurrentState);
	DrawDebugString(GetWorld(), GetOwner()->GetActorLocation(), logMsg, nullptr, FColor::Red, 0);


	switch (CurrentState)
	{
	case EBossState::Start:
		StartState ( DeltaTime );
		break;
	case EBossState::Idle:
		IdleState( DeltaTime );
		break;
	case EBossState::CoolDown:
		CoolDownState ( DeltaTime );
		break;
	case EBossState::Attack1:
		Attack1State( DeltaTime );
		break;
	case EBossState::Paused:
		PausedState ( DeltaTime );
		break;
	case EBossState::Attack2:
		Attack2State ( DeltaTime );
		break;
	case EBossState::Attack3:
		Attack3State( DeltaTime );
		break;
	case EBossState::Attack4:
		Attack4State( DeltaTime );
		break;
	case EBossState::Attack5:
		Attack5State( DeltaTime );
		break;
	case EBossState::Die:
		DieState ( DeltaTime );
		break;
	default:
		break;
	}
}



void UToolBoxBossFSM::ChangeState(EBossState NewState)
{
	CurrentState = NewState;
	AttackTimer = 0;

	// 애니메이션 동기화
	switch ( NewState )
	{
	case EBossState::Start:
		me->SetAnimState ( ERightArmAnimState::Start );
		break;
	case EBossState::Idle:
		me->SetAnimState ( ERightArmAnimState::Idle );
		break;
	case EBossState::CoolDown:
		me->SetAnimState ( ERightArmAnimState::CoolDown );
		break;
	case EBossState::Attack1:
		me->SetAnimState ( ERightArmAnimState::Attack1 );
		break;
	case EBossState::Paused:
		me->SetAnimState ( ERightArmAnimState::Paused );
		break;
	case EBossState::Attack2:
		me->SetAnimState ( ERightArmAnimState::Attack2 );
		break;
	case EBossState::Attack3:
		me->SetAnimState ( ERightArmAnimState::Attack3 );
		break;
	case EBossState::Attack4:
		me->SetAnimState ( ERightArmAnimState::Attack4 );
		break;
	case EBossState::Attack5:
		me->SetAnimState ( ERightArmAnimState::Attack5 );
		break;
	case EBossState::Die:
		me->SetAnimState ( ERightArmAnimState::Die );
		break;
	default:
		break;
	}

}

void UToolBoxBossFSM::StartState ( const float& DeltaTime )
{
	if ( !player || !me ) { return; }

	FVector dir = player->GetActorLocation ( ) - me->GetActorLocation ( );

	// 플레이어가 가까워지면 Attack1로 전이
	if ( dir.Size ( ) < AttackRange )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "StartState >> Attack1State" ) );
		UE_LOG ( LogTemp , Warning , TEXT ( "StartState >> Attack1State" ) );
		ChangeState ( EBossState::Attack1 );
	}
}

void UToolBoxBossFSM::IdleState( const float& DeltaTime )
{	
	bIsAttack1 = false;
	bIsAttack3 = false;

	if ( me->Lock1HP > 0 ) // 자물쇠1을 파괴하지 못했다면 공격1 상태를 반복한다.
	{
		ChangeState ( EBossState::Attack1 );
	}
	else if ( me->Lock1HP <= 0 && me->Lock2HP > 0 ) // 자물쇠2를 파괴하지 못했다면 공격3 ~ 공격1 상태를 반복한다.
	{
		if ( !bIsAttack2 )
		{
			ChangeState ( EBossState::Attack2 );
		}
		else if ( bIsAttack2 )
		{
			ChangeState ( EBossState::Attack3 );
		}
	}
	
}

void UToolBoxBossFSM::CoolDownState ( const float& DeltaTime )
{
	AttackCoolDown -= DeltaTime;

	if ( AttackCoolDown <= 0 )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "CoolDown >> Idle" ) );
		UE_LOG ( LogTemp , Warning , TEXT ( "CoolDown >> Idle" ) );
		ChangeState ( EBossState::Idle );
		AttackCoolDown = 3; // 쿨다운 시간 리셋
	}
}

void UToolBoxBossFSM::Attack1State ( const float& DeltaTime )
{
	if ( !player || !me ) { return; }

	// Attack1 벽에 닿아 멈춘 후 4초 유지 ( 못 박을 수 있는 제한시간 )
	AttackTimer += DeltaTime;
	if ( !bIsAttack1 )
	{
		if ( AttackTimer > Attack1Duration ) // 애니메이션 8초 + 4초가 지나면 쿨다운 상태로 전이
		{	
			GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "Attack1State >> CoolDown" ) );
			UE_LOG ( LogTemp , Warning , TEXT ( "Attack1State >> CoolDown" ) );
			ChangeState ( EBossState::CoolDown );

			bIsAttack1 = true;
			AttackTimer = 0; // 공격시간 리셋
		}
	}
}

void UToolBoxBossFSM::PausedState ( const float& DeltaTime )
{	
	// 일시정지 상태에서 12초간 유지 ( 자물쇠 파괴할 수 있는 제한시간 )
	AttackTimer += DeltaTime;

	if ( AttackTimer <= Attack1Duration )
	{
		if ( me->Lock1HP > 0 ) // 자물쇠1이 존재할 때
		{
			if ( me->Lock1HP == 0 ) // 자물쇠1이 파괴된다면 /////여기서부터 안들어옴
			{
				GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "Destroyed Lock1 PausedState >> CoolDown" ) );
				UE_LOG ( LogTemp , Warning , TEXT ( "Destroyed Lock1 >> CoolDown" ) );

				// 쿨다운 -> 공격2 상태로 전이
				ChangeState ( EBossState::CoolDown );
				AttackTimer = 0; // 공격시간 리셋
				return; // 상태를 바꿨으므로 함수 종료
			}
		}
		else if ( me->Lock1HP == 0 && me->Lock2HP > 0 ) // 자물쇠1이 없고 자물쇠2만 있을 때
		{
			if ( me->Lock2HP == 0 ) // 자물쇠2가 파괴된다면
			{
				ChangeState( EBossState::Die );
				AttackTimer = 0; // 공격시간 리셋
				return; // 상태를 바꿨으므로 함수 종료
			}
		}
	}
	else if( AttackTimer > Attack1Duration ) // 제한시간이 초과했을 때
	{
		// 쿨다운 상태로 전이
		ChangeState ( EBossState::CoolDown );
		AttackTimer = 0; // 공격시간 리셋
	}
}

void UToolBoxBossFSM::Attack2State( const float& DeltaTime )
{
	AttackTimer += DeltaTime;

	if ( !bIsAttack2 )
	{
		me->Drill->SetVisibility(true);
		me->DrillCircle->SetVisibility ( true );
		bIsAttack2 = true;
	}
	if ( AttackTimer > Attack2Duration ) // 바닥뚫기가 끝나면
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "Attack2State >> Attack3State" ) );
		UE_LOG ( LogTemp , Warning , TEXT ( "Attack2State >> Attack3State" ) );
		
		// 드릴 회전 공격으로 전이
		ChangeState(EBossState::Attack3);
		AttackTimer = 0; // 공격시간 리셋
	}
}

void UToolBoxBossFSM::Attack3State( const float& DeltaTime )
{
	AttackTimer += DeltaTime;

	if ( !bIsAttack3 )
	{	
		me->Drill->SetVisibility ( true );
		me->DrillCircle->SetVisibility ( true );
		me->DrillArms->SetVisibility ( true );

		bIsAttack3 = true;
		
	}
	if ( AttackTimer > Attack3Duration ) // 드릴 회전 공격이 끝나면
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "Attack3State >> Attack1State" ) );
		UE_LOG ( LogTemp , Warning , TEXT ( "Attack3State >> Attack1State" ) );

		AttackTimer = 0; // 공격시간 리셋

		me->Drill->SetVisibility ( false );
		me->DrillCircle->SetVisibility ( false );
		me->DrillArms->SetVisibility ( false );

		bIsAttack3 = false;
		bIsAttack1 = false;

		// 공격1 상태로 전이
		ChangeState ( EBossState::Attack1 );

	}
}

void UToolBoxBossFSM::Attack4State( const float& DeltaTime )
{
	
}

void UToolBoxBossFSM::Attack5State( const float& DeltaTime )
{
	
}

void UToolBoxBossFSM::DieState ( const float& DeltaTime )
{

	GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "Die State" ) );
	UE_LOG ( LogTemp , Warning , TEXT ( "Die State" ) );

	if ( !player || !me ) { return; }

	// Enter ragdoll state if not already in ragdoll
	//if ( !bIsInRagdoll )
	//{
	me->EnterRagdollState ( );
	//bIsInRagdoll = true;
//}
}