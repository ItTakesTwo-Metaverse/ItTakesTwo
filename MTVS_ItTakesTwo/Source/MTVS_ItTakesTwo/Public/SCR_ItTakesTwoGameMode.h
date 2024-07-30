// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SCR_ItTakesTwoGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API ASCR_ItTakesTwoGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
// ��ȯ�� ĳ���͵� �������Ʈ ���.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ACSR_Player_Cody> SpawnCody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ACSR_Player_May> SpawnMay;

// ��ȯ�� ĳ���͵� ����.
	class ACSR_Player_Cody *P2_Cody;

	class ACSR_Player_May *P1_May;

};
