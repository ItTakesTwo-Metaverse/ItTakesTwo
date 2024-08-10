// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSR_P_AComp_CharicStateMannage.generated.h"

const int32 IDLE        = 0x0000; //0000 0000 0000 0000
const int32 MOVE        = 0x0001; //0000 0000 0000 0001
const int32 JUMPMOVE    = 0x0002; //0000 0000 0000 0010
const int32 RUN         = 0x0004; //0000 0000 0000 0100 
const int32 AIRMOVE     = 0x0008; //0000 0000 0000 1000 
const int32 SIT         = 0x0010; //0000 0000 0001 0000 
const int32 AIRSIT      = 0x0020; //0000 0000 0010 0000     
const int32 JUMP        = 0x0040; //0000 0000 0100 0000 
const int32 SCJUMP      = 0x0080; //0000 0000 1000 0000 
const int32 DASH        = 0x0100; //0000 0001 0000 0000 
const int32 DAMAGED     = 0x0200; //0000 0010 0000 0000 
const int32 PRESS       = 0x0400; //0000 0100 0000 0000 
const int32 DIE         = 0x0800; //0000 1000 0000 0000  

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MTVS_ITTAKESTWO_API UCSR_P_AComp_CharicStateMannage : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSR_P_AComp_CharicStateMannage();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
    // 현재 상태를 저장
    int32 CurrentState = IDLE;

    // 변환하려고 하는 상태로 가도 되는지 확인
    virtual bool TotalControlState( int32 NewState );

    // 현재 상태에 새로운 상태 추가
    bool AddState( int32 NewState );

    // 현재 상태에 지정한 상태 제거
    void RemoveState( int32 DeleteState );

    bool CanAddMove( );
    bool CanAddPress ( );
    bool CanAddJumpMove ( );
    bool CanAddJump( );
};
