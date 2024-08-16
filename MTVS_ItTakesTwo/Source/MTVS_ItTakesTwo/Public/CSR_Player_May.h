// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSR_P_Player.h"
#include "CSR_Player_May.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API ACSR_Player_May : public ACSR_P_Player
{
	GENERATED_BODY()
public:
	ACSR_Player_May ( );
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// PlayerController를 IMC_PlayerController와 맵핑.
	void MakeEnhancedInputLocalSubSystem();
#pragma region
public:
	UPROPERTY(EditDefaultsOnly )
	class USceneComponent *HammerLocation;

	UPROPERTY ( EditDefaultsOnly )
	class UCSR_C_AComp_InputBIndMay* KeyBindComponent;

	UPROPERTY(EditDefaultsOnly )
	class UCSR_MayUseHammerObj *UseHammerComp;

	UPROPERTY()
	class UCSR_MayAnimation *AnimMay;

	FVector HammerPlayerSocketLotation;

	UFUNCTION(BlueprintNativeEvent )
	void ChangeCharacterColor( );

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> PlayerHPWidget;

	class UCSR_PlayerWidget *MayUI;

	UFUNCTION(BlueprintCallable)
	void TranceSIn();
	UFUNCTION(BlueprintCallable)
	void LightOn();

	UFUNCTION(BlueprintCallable)
	void tranReBorn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxR = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CurR = 0;

#pragma endregion
};
