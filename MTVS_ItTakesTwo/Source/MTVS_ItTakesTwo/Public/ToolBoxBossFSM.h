// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ToolBoxBossFSM.generated.h"

// 상태정의
UENUM(BlueprintType)
enum class EBossState : uint8
{
	//Start,
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
	
	// 소유 액터
	UPROPERTY()
	class AToolboxBoss* me;

	UPROPERTY()
	class ACharacter* player;

	//UPROPERTY()
	//class AHSW_Player* HSWplayer;

	UPROPERTY(EditAnywhere)
	float AttackRange = 1000.0f;
	float AttackCoolDown;
	float AttackTimer;
	float Attack1Duration;

	bool bAttack1Executed;



	// 상태변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EBossState CurrentState;
	
	void ChangeState(EBossState NewState);

	//void StartState();
	void IdleState();
	void Attack1State();
	void Attack2State();
	void Attack3State();
	void Attack4State();
	void Attack5State();
	void CoolDownState();
	void DieState();

	
		
};
