// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSW_Bullet.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API AHSW_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHSW_Bullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//�浹ü, �ܰ��� �����ʹ�.
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MeshComp;

	//�߻�ü ������Ʈ�� �����ʹ�.
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* MovementComp;
};
