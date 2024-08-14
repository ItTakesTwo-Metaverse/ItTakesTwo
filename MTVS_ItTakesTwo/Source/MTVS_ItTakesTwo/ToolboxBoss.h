// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RightArmAnimInstance.h"
#include "DrillCircleAnimInstance.h"
#include "ToolboxBoss.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API AToolboxBoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AToolboxBoss();

	void SetAnimState ( ERightArmAnimState NewState );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* LeftArmMesh;

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* RightArmMesh;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* NailInteractionBox1;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* NailInteractionBox2;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* NailInteractionBox3;
	
	UPROPERTY( EditDefaultsOnly )
	class USkeletalMeshComponent* Lock1;
	UPROPERTY( EditDefaultsOnly )
	class USkeletalMeshComponent* LockBody1;
	UPROPERTY ( EditDefaultsOnly )
	class USkeletalMeshComponent* Lock2;
	UPROPERTY( EditDefaultsOnly )
	class USkeletalMeshComponent* LockBody2;

	UPROPERTY(EditDefaultsOnly )
	class UStaticMeshComponent* Drill;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite )
	class USkeletalMeshComponent* DrillCircle;
	
	UPROPERTY(EditDefaultsOnly )
	class USkeletalMeshComponent* DrillArms;

	UPROPERTY( EditDefaultsOnly )
	float Lock1HP = 5;
	float Lock2HP = 5;
	float damage = 1;

	bool bCanDamage=true;


	FTimerHandle Lock1DestroyTimerHandle;
	FTimerHandle Lock2DestroyTimerHandle;

	// 보스 오른팔 충돌했을 때 플레이어 파괴
	UFUNCTION()
	void OnMyBossBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// 보스 오른팔 타겟박스 못 상호작용했을 때 보스 일시정지 상태로 전이
	UFUNCTION()
	void OnMyNailInteractionBoxBeginOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	// 자물쇠 망치공격 당했을 때 자물쇠 데미지
	UFUNCTION()
	void OnMyLockBeginOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	UFUNCTION( )
	void DestroyLock1 ( );
	
	UFUNCTION( )
	void DestroyLock2( );

	 UFUNCTION()
    void OnMyDrillCirleOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	 UFUNCTION()
    void OnMyDrillOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void EnterRagdollState( );

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UToolBoxBossFSM* fsm;

	UPROPERTY()
    class URightArmAnimInstance* RightArmAnimInstance;

	UPROPERTY()
    class UDrillCircleAnimInstance* DrillCircleAnim;

	UPROPERTY ( )
	class ACSR_P_Player* Player;
	

};
