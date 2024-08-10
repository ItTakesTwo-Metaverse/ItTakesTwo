// Fill out your copyright notice in the Description page of Project Settings.


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

	AttackCoolDown = 5; // 예시로 5초 쿨다운 설정
	AttackTimer = 0;
	Attack1Duration = 12;
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
	case EBossState::DestroyRightArm:
		DestroyRightArmState ( DeltaTime );
		break;
	case EBossState::Attack2Drill:
		Attack2DrillState ( DeltaTime );
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
	case EBossState::DestroyRightArm:
		me->SetAnimState ( ERightArmAnimState::DestroyRightArm );
		break;
	case EBossState::Attack2Drill:
		me->SetAnimState ( ERightArmAnimState::Attack2Drill );
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
	if ( me->LockHP > 5 ) // 자물쇠가 2개라면 공격1을 반복한다.
	{
		ChangeState ( EBossState::Attack1 );
	}
	else if ( me->LockHP <= 5 ) // 자물쇠가 1개라면 공격2(드릴) 상태로 전이한다.
	{
		ChangeState ( EBossState::Attack2Drill );
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
		AttackCoolDown = 5; // 쿨다운 시간 리셋
	}
}

void UToolBoxBossFSM::Attack1State ( const float& DeltaTime )
{
	if ( !player || !me ) { return; }

	// Attack1 벽에 닿아 멈춘 후 4초 유지 ( 못 박을 수 있는 제한시간 )
	AttackTimer += DeltaTime;
	// 4초가 지나면 쿨다운 상태로 전이
	if ( AttackTimer >= Attack1Duration )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "Attack1State >> CoolDown" ) );
		UE_LOG ( LogTemp , Warning , TEXT ( "Attack1State >> CoolDown" ) );
		ChangeState ( EBossState::CoolDown );

		AttackTimer = 0; // 공격시간 리셋
	}
	
}

void UToolBoxBossFSM::PausedState ( const float& DeltaTime )
{	
	// 일시정지 상태에서 12초간 유지 ( 자물쇠 파괴할 수 있는 제한시간 )
	AttackTimer += DeltaTime;

	if( AttackTimer >= Attack1Duration ) // 제한시간이 초과했을 때
	{
		if ( me->LockHP <= 5 ) // 자물쇠가 1개 파괴된다면
		{
			GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "Destroyed Lock1 / PausedState >> CoolDownState" ) );
			UE_LOG ( LogTemp , Warning , TEXT ( "Destroyed Lock1 / PausedState >> CoolDownState" ) );

			// 쿨다운 상태로 전이
			ChangeState ( EBossState::CoolDown );
		}
		else if ( me->LockHP <= 0 ) // 현재 체력이 0이라면
		{
			GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "Destroyed Lock2 PausedState >> DestroyRightArmState" ) );
			UE_LOG ( LogTemp , Warning , TEXT ( "Destroyed Lock2 >> DestroyRightArmState" ) );

			// 죽음 상태로 전이
			ChangeState ( EBossState::DestroyRightArm );
		}

		AttackTimer = 0; // 공격시간 리셋
	}
	

	
}

void UToolBoxBossFSM::DestroyRightArmState ( const float& DeltaTime )
{

	GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "Destroy Right Arm State" ) );
	UE_LOG ( LogTemp , Warning , TEXT ( "Destroy Right Arm State" ) );

	if ( !player || !me ) { return; }

	// Enter ragdoll state if not already in ragdoll
	//if ( !bIsInRagdoll )
	//{
		me->EnterRagdollState ( );
		//bIsInRagdoll = true;
	//}
}

void UToolBoxBossFSM::Attack2DrillState( const float& DeltaTime )
{
	//if ( !bIsAttackDrill )
	//{
		//bIsAttackDrill = true;
		me->Drill->SetVisibility(true);
		
	//}
}

void UToolBoxBossFSM::Attack3State( const float& DeltaTime )
{
	
}

void UToolBoxBossFSM::Attack4State( const float& DeltaTime )
{
	
}

void UToolBoxBossFSM::Attack5State( const float& DeltaTime )
{
	
}

