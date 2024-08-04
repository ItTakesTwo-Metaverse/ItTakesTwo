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

	// 못 발사시킬 IA, 함수
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_Fire;
	void OnMyActionFire ( );

	// 못 회수할 IA, 함수
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_Back;
	void OnMyActionBack ( );


	// 회수할때 필요한 Nail 변수
	class AHSW_Bullet* Nail;

	// 스폰할때 필요한 Nail Factory
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHSW_Bullet> NailFactory;

};
