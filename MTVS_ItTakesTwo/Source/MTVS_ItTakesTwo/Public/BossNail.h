﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossNail.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API ABossNail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossNail();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly )
	class UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly )
	class UStaticMeshComponent* MeshComp;

	void SetActive ( bool bValue );

	UPROPERTY(EditAnywhere )
	float Speed = 1000.f;
	FVector Dir;

	bool bShoot;

	void Shoot (float DeltaTime );


};
