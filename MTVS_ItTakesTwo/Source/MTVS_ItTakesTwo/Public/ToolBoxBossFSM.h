﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ToolBoxBossFSM.generated.h"

// 상태정의
UENUM(BlueprintType)
enum class EBossState : uint8
{
	Start,
	Idle,
	CoolDown ,
	Attack1,
	Paused,
	Attack2 ,
	Attack3 ,
	Attack4, 
	Attack5,
	Die
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MTVS_ITTAKESTWO_API UToolBoxBossFSM : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UToolBoxBossFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	
	// 소유 액터
	UPROPERTY()
	class AToolboxBoss* me;

	UPROPERTY()
	class ACharacter* player1;
	
	UPROPERTY()
	class ACharacter* player2;

	UPROPERTY( )
	class UDrillCircleAnimInstance* DrillCircleAnim;
	
	UPROPERTY( )
	class UDrillArmsAnimInstance* DrillArmsAnim;

	UPROPERTY(EditAnywhere)
	float AttackRange = 4050.0f;
	float AttackCoolDown;
	float AttackTimer;
	float Attack1Duration;
	float Attack2Duration;
	float Attack3Duration;
	float Attack4Duration;

	bool DestroyedLock1 = false;

	bool bIsInRagdoll = false;
	bool bIsAttack1 = false;
	bool bIsAttack2 = false;
	bool bIsAttack3 = false;
	bool bIsAttack4 = false;

	// 상태변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EBossState CurrentState;
	
	void ChangeState(EBossState NewState);

	void StartState( const float& DeltaTime );
	void IdleState( const float& DeltaTime );
	void CoolDownState ( const float& DeltaTime );
	void Attack1State( const float& DeltaTime );
	void PausedState ( const float& DeltaTime );
	void Attack2State( const float& DeltaTime );
	void Attack3State( const float& DeltaTime );
	void Attack4State( const float& DeltaTime );
	void Attack5State( const float& DeltaTime );
	void DieState ( const float& DeltaTime );
	

	FTimerHandle DrillOnTimerHandle;
	FTimerHandle DrillOffTimerHandle;
	FTimerHandle DrillArmOnTimerHandle;
	FTimerHandle DrillArmOffTimerHandle;

	FTimerHandle DrillOn4TimerHandle;
	FTimerHandle DrillOff4TimerHandle;
	FTimerHandle DrillArmOn4TimerHandle;
	FTimerHandle DrillArmOff4TimerHandle;

	void DrillOn ( );
	void DrillOff ( );
	void DrillArmOn ( );
	void DrillArmOff ( );
};
