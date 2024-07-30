// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBoxBossFSM.h"
#include "../ToolboxBoss.h"

// Sets default values for this component's properties
UToolBoxBossFSM::UToolBoxBossFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AttackCoolDown = 3.0f; // 예시로 3초 쿨다운 설정
	AttackTimer = 0;
}


// Called when the game starts
void UToolBoxBossFSM::BeginPlay()
{
	Super::BeginPlay();

	//Cast<AToolboxBoss>(GetComponentTransform());
	
}


// Called every frame
void UToolBoxBossFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 실행창에 상태 메세지 출력
	FString logMsg = UEnum::GetValueAsString(CurrentState);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, logMsg);

	AttackTimer += DeltaTime;

	switch (CurrentState)
	{
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
		AttackCoolDown -= DeltaTime;
		if (AttackCoolDown <= 0)
		{
			ChangeState(EBossState::Idle);
			AttackCoolDown = 3.0f; // 쿨다운 시간 리셋
		}
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
}

void UToolBoxBossFSM::IdleState()
{
	// 기본 상태
}

void UToolBoxBossFSM::Attack1State()
{
	// 오른팔 내려쳐서 쓰는 공격
	
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
	ChangeState(EBossState::CoolDown);
}

void UToolBoxBossFSM::DieState()
{

}

