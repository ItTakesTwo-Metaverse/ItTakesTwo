// Fill out your copyright notice in the Description page of Project Settings.

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
	DestroyRightArm,
	Attack2Drill1 ,
	Attack3, 
	Attack4, 
	Attack5
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


	UPROPERTY(EditAnywhere)
	float AttackRange = 3000.0f;
	float AttackCoolDown;
	float AttackTimer;
	float Attack1Duration;

	bool bIsInRagdoll = false;
	bool bIsAttackDrill = false;

	// 상태변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EBossState CurrentState;
	
	void ChangeState(EBossState NewState);

	void StartState( const float& DeltaTime );
	void IdleState( const float& DeltaTime );
	void CoolDownState ( const float& DeltaTime );
	void Attack1State( const float& DeltaTime );
	void PausedState ( const float& DeltaTime );
	void DestroyRightArmState ( const float& DeltaTime );
	void Attack2Drill1State( const float& DeltaTime );
	void Attack3State( const float& DeltaTime );
	void Attack4State( const float& DeltaTime );
	void Attack5State( const float& DeltaTime );
	

};
