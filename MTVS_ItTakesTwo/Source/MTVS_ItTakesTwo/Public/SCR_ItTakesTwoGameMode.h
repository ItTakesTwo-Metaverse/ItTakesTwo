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
	virtual void InitGame ( const FString& MapName , const FString& Options , FString& ErrorMessage );


	virtual void BeginPlay() override;
public:
	ASCR_ItTakesTwoGameMode ();

// 소환할 캐릭터들 블루프린트 등록.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	TSubclassOf<class ACSR_Player_Cody> SpawnCody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	TSubclassOf<class ACSR_Player_May> SpawnMay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite )
	class UCustomGameViewportClient * CustomViewportClient;

// 소환한 캐릭터들 저장.

	UPROPERTY(EditAnywhere, BlueprintReadWrite )
	class ACSR_Player_Cody *P2_Cody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite )
	class ACSR_Player_May *P1_May;

	void SetMayDie( bool flag );

	void SetCodyDie( bool flag );

	bool MayDie = false;

	bool CodyDie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	float view33 = 0.33f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	float view66 = 0.66f;

	void ChangeMaps( );

	UFUNCTION(BlueprintCallable )
	class UCustomGameViewportClient* GetCustomViewportClient ();

	UFUNCTION(BlueprintCallable )
	void CallCutSin();

	UFUNCTION(BlueprintImplementableEvent )
	void CodyDieMap( );

	UFUNCTION(BlueprintImplementableEvent )
	void MayDieMap( );

	UFUNCTION(BlueprintImplementableEvent )
	void MayCodyAllDieMap( );

	UFUNCTION ( BlueprintImplementableEvent )
	void MayCodyAllAliveMap( );

	UFUNCTION ( BlueprintImplementableEvent )
	void CutSinMap( );

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AToolboxBoss *boss;

	UFUNCTION(BlueprintCallable )
	void LightOn();

	UFUNCTION(BlueprintCallable )
	void LightOff();
};

