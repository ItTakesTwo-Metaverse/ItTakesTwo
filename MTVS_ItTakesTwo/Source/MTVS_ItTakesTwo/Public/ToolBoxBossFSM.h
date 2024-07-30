// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ToolBoxBossFSM.generated.h"

// ��������
UENUM(BlueprintType)
enum class EBossState : uint8
{
	Idle, 
	Attack1, 
	Attack2, 
	Attack3, 
	Attack4, 
	Attack5,
	CoolDown, 
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
	// ���º���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EBossState CurrentState = EBossState::Idle;

	float AttackCoolDown;
	float AttackTimer;

	void ChangeState(EBossState NewState);

	void IdleState();
	void Attack1State();
	void Attack2State();
	void Attack3State();
	void Attack4State();
	void Attack5State();

	void CoolDownState();
	void DieState();

	

	
		
};
