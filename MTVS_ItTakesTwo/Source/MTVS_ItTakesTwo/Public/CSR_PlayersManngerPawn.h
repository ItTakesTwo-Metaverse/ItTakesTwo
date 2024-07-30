// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CSR_PlayersManngerPawn.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API ACSR_PlayersManngerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACSR_PlayersManngerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
#pragma region
	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext *IMC_PlayerController;
	// ĳ���� ���� �׼� ��ư
	UPROPERTY(EditDefaultsOnly)
	class UInputAction *SELF_CreateCharactorButton;

	void MakeEnhancedInputLocalSubSystem();
#pragma endregion KeyMappingHeader

public:
#pragma region
	// �������Ʈ�� �� ���ε� �ؾ��ϴ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> SpawnCharactorA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> SpawnCharactorB;

	
	// �Լ�
	void SpawnPlayers();
#pragma endregion createPlayerHeader
};
