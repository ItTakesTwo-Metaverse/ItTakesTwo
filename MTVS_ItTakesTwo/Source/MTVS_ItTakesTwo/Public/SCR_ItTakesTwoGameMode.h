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
// 소환할 캐릭터들 블루프린트 등록.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	TSubclassOf<class ACSR_Player_Cody> SpawnCody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	TSubclassOf<class ACSR_Player_May> SpawnMay;

// 소환한 캐릭터들 저장.
	class ACSR_Player_Cody *P2_Cody;

	class ACSR_Player_May *P1_May;

};
