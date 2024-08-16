// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSR_PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API UCSR_PlayerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION( BlueprintImplementableEvent )
	void InitHP(float HP );

	UFUNCTION(BlueprintCallable )
	float InitHPBar(float HP );

	UFUNCTION(BlueprintCallable )
	float TakeDamage(float CurHP , float MaxHP);

	UFUNCTION ( BlueprintImplementableEvent )
	void TakeDamageEvent ( float CurHP , float MaxHP );
	
	UFUNCTION(BlueprintCallable)
	float RebornJung(float DeltaTIme);

	UPROPERTY (BlueprintReadWrite)
	float MemoHP = 0;
	
	UPROPERTY ( BlueprintReadWrite )
	float TargetHP = 0;

	UPROPERTY(BlueprintReadWrite)
	float TargetRebone = 1;

	UPROPERTY(BlueprintReadWrite)
	float MemoRebone = 0;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetOnRebornUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetOffRebornUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetOnHPUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetOffHPUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	float CountReboneTime(float a);

	UFUNCTION(BlueprintImplementableEvent)
	void StartHeartBeat(float DeltaTime);



	//UFUNCTION(BlueprintCallable )
	//void TakeDelayDamage( );

	UFUNCTION(BlueprintCallable )
	float DecreaseDelayBar ( FTimerHandle TimerHandle );

	//UPROPERTY( )
	//FTimerHandle TimerHandle;
};
