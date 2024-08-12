// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSR_BaseAnimation.h"
#include "CSR_P_AComp_CharicStateMannage.generated.h"

const int32 IDLE =		0x00010000;
const int32 DIE =		0x00000001;
const int32 REBORN =	0x00000002;
const int32 INVI =		0x00000004;
const int32 PRESS =		0x00000008;
const int32 DAMAGED =	0x00000010;
const int32 ZOOM =		0x00000020;
const int32 FIRE =		0x00000040;
const int32 ATTACK =	0x00000080;
const int32 AIRSIT =	0x00000100;
const int32 SIT =		0x00000200;
const int32 DASH =		0x00000400;
const int32 SCJUMP =	0x00000800;
const int32 JUMPMOVE =	0x00001000;
const int32 JUMP =		0x00002000;
const int32 RUN =		0x00004000;
const int32 MOVE =		0x00008000;

UCLASS ( ClassGroup = (Custom) , meta = (BlueprintSpawnableComponent) )
class MTVS_ITTAKESTWO_API UCSR_P_AComp_CharicStateMannage : public UActorComponent
{
	GENERATED_BODY ( )

public:
	// Sets default values for this component's properties
	UCSR_P_AComp_CharicStateMannage ( );

protected:
	// Called when the game starts
	virtual void BeginPlay ( ) override;

public:
	// 애니메이션 동작하는 부분
	class UCSR_BaseAnimation* Anim;

	// 현재 상태를 저장
	int32 CurrentState = IDLE;

	// 변환하려고 하는 상태로 가도 되는지 확인
	virtual bool TotalControlState ( int32 NewState );

	// 현재 상태에 새로운 상태 추가
	bool AddState ( int32 NewState );

	// 현재 상태에 지정한 상태 제거
	void RemoveState ( int32 DeleteState );

	void SpendStateToAnim ( );

	//void SetAnims ( class UCSR_BaseAnimation* NewAnim);

	bool CanAddMove ( );
	bool CanAddPress ( );
	bool CanAddJumpMove ( );
	bool CanAddJump ( );
	bool CanAddRun ( );
	bool CanAddDie ( );
	bool CanAddReBorn ( );
	bool CanAddIniv ( );
	bool CanAddAttack ( );
};
