// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSR_CodyPile.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MTVS_ITTAKESTWO_API UCSR_CodyPile : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSR_CodyPile();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditDefaultsOnly )
	class ACSR_Player_Cody *charic_;

	UPROPERTY(EditDefaultsOnly )
	class USpringArmComponent *SpringArmComp_;

	UPROPERTY(EditDefaultsOnly )
	class UCameraComponent *CameraComp_;
	
	UPROPERTY(EditDefaultsOnly, Category = "ModifyAble" )
	class UCSR_PileInventory *PileInven;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	TSubclassOf<class UUserWidget> CrosshairUIFactory;

	UPROPERTY ( )
	class UUserWidget* CrosshairUI;

	UPROPERTY(EditDefaultsOnly )
	FVector InitArmOffsetLocation = FVector(0.0f, 0.0f ,0.0f );

	UPROPERTY(EditDefaultsOnly )
	FVector AfterArmOffsetLocation = FVector(0.0f, 200.0f, 200.0f );

	UPROPERTY(EditDefaultsOnly )
	float InitArmSpringDistance = 1000.0f;

	UPROPERTY(EditDefaultsOnly )
	float AfterArmSpringDistance = 450.0f;

	UPROPERTY(EditDefaultsOnly )
	float InitCameraFov = 90.0f;

	UPROPERTY(EditDefaultsOnly )
	float AfterCameraFov = 90.0f;

	void InitComp(class UCameraComponent* CameraComp , class USpringArmComponent* SpringArm, float ArmSpringDistance , class ACSR_Player_Cody *charic);

	bool ExecToggle = false;

	bool CurrentToggle = false;

	void ToggleButton ( bool ChangeToggle );

	void InZooming ( float DetaTIme );
	
	void OutZooming ( float DetaTIme );
	
	void CameraZoomInMoving ( float DetaTime );
	
	void CameraZoomOutMoving ( float DetaTime );

	FVector LayCasting ( );

	void OnMyActionFire ( FVector startLocation, FRotator startRotation );

	void OnMyActionBack ( );

	//---------------------------------------------
	UPROPERTY(EditAnywhere,BlueprintReadWrite )
	TSubclassOf<class AHSW_BulletManager> NailBagFactory;

	UPROPERTY(EditDefaultsOnly )
	class AHSW_BulletManager* NailBag;
};
