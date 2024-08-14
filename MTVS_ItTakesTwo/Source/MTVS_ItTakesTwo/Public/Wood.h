﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wood.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API AWood : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* WoodCube;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* WoodSide;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* WoodCircle1;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* WoodCircle2;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* WoodCircle3;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* WoodCircle4;


	UPROPERTY ( )
	class UNiagaraSystem* WoodEffect;

	UFUNCTION( )
	void OnMyWoodCircle1Effect( );
	UFUNCTION( )
	void OnMyWoodCircle2Effect( );
	UFUNCTION( )
	void OnMyWoodCircle3Effect( );
	UFUNCTION( )
	void OnMyWoodCircle4Effect( );

};
