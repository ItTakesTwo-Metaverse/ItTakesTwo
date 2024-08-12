// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossNailSpawner.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API ABossNailSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossNailSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere )
	class USceneComponent* RootComp;

	void PlayNailAttack ( );

	float CurrentTime;
	UPROPERTY(EditAnywhere )
	float MakeTine = 1.0f;

	void DropNail ( );

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABossNail> NailFactory;

	int32 NailMaxCount = 10;

	APawn* Player1;
	APawn* Player2;
};
