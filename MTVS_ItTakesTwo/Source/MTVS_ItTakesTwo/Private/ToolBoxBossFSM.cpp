// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBoxBossFSM.h"
#include "../ToolboxBoss.h"
#include "HSW_Player.h"
#include "GameFramework/Character.h"
#include "RightArmAnim.h"
#include "Animation/AnimMontage.h"

// Sets default values for this component's properties
UToolBoxBossFSM::UToolBoxBossFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AttackCoolDown = 3.0f; // 예시로 3초 쿨다운 설정
	AttackTimer = 0;
	Attack1Duration = 10;
	//bAttack1Executed = false;
}


// Called when the game starts
void UToolBoxBossFSM::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AToolboxBoss>(GetOwner());
	player = Cast<ACharacter> ( GetWorld ( )->GetFirstPlayerController ( )->GetCharacter ( ) );

	// 초기 상태를 Idle로 설정
	ChangeState(EBossState::Idle);
}


// Called every frame
void UToolBoxBossFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 실행창에 상태 메세지 출력
	FString logMsg = UEnum::GetValueAsString(CurrentState);
	DrawDebugString(GetWorld(), GetOwner()->GetActorLocation(), logMsg, nullptr, FColor::Red, 0);

	AttackTimer += DeltaTime;

	switch (CurrentState)
	{
	//case EBossState::Start:
	//	StartState ();
	//	//CoolDownState ();
	case EBossState::Idle:
		IdleState();
		CoolDownState();
		break;
	case EBossState::Attack1:
		Attack1State();
		CoolDownState();
		break;
	case EBossState::Attack2:
		Attack2State();
		CoolDownState();
		break;
	case EBossState::Attack3:
		Attack3State();
		CoolDownState();
		break;
	case EBossState::Attack4:
		Attack4State();
		CoolDownState();
		break;
	case EBossState::Attack5:
		Attack5State();
		CoolDownState();
		break;
	case EBossState::CoolDown:
		CoolDownState();
		break;
	case EBossState::Die:
		DieState();
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
	/*case EBossState::Start:
		me->SetAnimState ( ERightAnimState::Start );
		GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Green , TEXT ( "Set Anim State : Start" ) );
		break;*/
	case EBossState::Idle:
		me->SetAnimState ( ERightAnimState::Idle );
		GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Green , TEXT ( "Set Anim State : Idle" ) );
		break;
	case EBossState::Attack1:
		me->SetAnimState ( ERightAnimState::Attack1 );
		GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Green , TEXT ( "Set Anim State : Attack1" ) );
		break;
	case EBossState::Attack2:
		me->SetAnimState ( ERightAnimState::Attack2 );
		break;
	case EBossState::Attack3:
		me->SetAnimState ( ERightAnimState::Attack3 );
		break;
	case EBossState::Attack4:
		me->SetAnimState ( ERightAnimState::Attack4 );
		break;
	case EBossState::Attack5:
		me->SetAnimState ( ERightAnimState::Attack5 );
		break;
	case EBossState::CoolDown:
		me->SetAnimState ( ERightAnimState::CoolDown );
		GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Green , TEXT ( "Set Anim State : CoolDown" ) );
		break;
	case EBossState::Die:
		me->SetAnimState ( ERightAnimState::Die );
		break;
	default:
		break;
	}

}

//void UToolBoxBossFSM::StartState ( )
//{
//	if ( !player || !me ) { return; }
//
//	FVector dir = player->GetActorLocation ( ) - me->GetActorLocation ( );
//
//	// 플레이어가 가까워지면 Attack1로 전이
//	if ( dir.Size ( ) < AttackRange /*&& !bAttack1Executed*/ )
//	{
//		GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "StartState >> AttackState" ) );
//		ChangeState ( EBossState::Attack1 );
//		//bAttack1Executed = true;
//	}
//}

void UToolBoxBossFSM::IdleState()
{	
	if ( !player || !me ){ return; }

	FVector dir = player->GetActorLocation() - me->GetActorLocation();

	// 플레이어가 가까워지면 Attack1로 전이
	if (dir.Size() < AttackRange /*&& !bAttack1Executed*/)
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "idlestate >> attackstate" ) );
		ChangeState ( EBossState::Attack1 );
		//bAttack1Executed = true;
	}
}

void UToolBoxBossFSM::Attack1State()
{
	GEngine->AddOnScreenDebugMessage ( -1 , 2.f , FColor::Blue , TEXT ( "Attack1!!!" ) );
	
	if ( !player || !me ){ return; }
	ChangeState ( EBossState::CoolDown );
	// Attack1 상태 유지
	/*AttackTimer += GetWorld()->GetDeltaSeconds();
	if ( AttackTimer >= Attack1Duration )
	{
		ChangeState ( EBossState::CoolDown );
	}*/



	/*if ( 못이 박혔다면 공격1 상태를 유지하고 애니메이션을 일시정지 하고싶다. )
	{
		if ( 데미지가 1 / 2(자물쇠)만큼 입었다면 쿨다운 >> 다시 공격1 상태로 돌아오자 )
		{
			ChangeState ( EBossState::CoolDown );
		}
			
	}*/
	
}

void UToolBoxBossFSM::Attack2State()
{
	
}

void UToolBoxBossFSM::Attack3State()
{
	
}

void UToolBoxBossFSM::Attack4State()
{
	
}

void UToolBoxBossFSM::Attack5State()
{
	
}

void UToolBoxBossFSM::CoolDownState()
{
	
	AttackCoolDown -= GetWorld()->GetDeltaSeconds();
	if ( AttackCoolDown <= 0 )
	{	
		ChangeState ( EBossState::Idle );
		AttackCoolDown = 3.0f; // 쿨다운 시간 리셋
		//bAttack1Executed = false; // 후에 다른 공격 허용하도록 재설정
	}
}

void UToolBoxBossFSM::DieState()
{
	
}

