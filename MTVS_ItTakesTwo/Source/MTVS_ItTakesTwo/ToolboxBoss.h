// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ToolboxBoss.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API AToolboxBoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AToolboxBoss();

	void SetAnimState ( ERightAnimState NewState );

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
	
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Lock1;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Lock2;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHP = 10;

	UFUNCTION()
	void OnMyBossBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnMyNailInteractionBoxBeginOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	UFUNCTION()
	void OnMyLockBeginOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UToolBoxBossFSM* fsm;

	UPROPERTY()
    class URightArmAnim* RightArmAnimInstance;

	UFUNCTION()
	void EnterRagdollState( );
};
