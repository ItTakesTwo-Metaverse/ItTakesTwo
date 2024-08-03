// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HSW_Player.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API AHSW_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHSW_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* IMC_Player;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_Fire;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_Back;

	void OnMyActionFire();
	void OnMyActionBack ( );

	class AHSW_Bullet* Nail;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHSW_Bullet> NailFactory;

};
