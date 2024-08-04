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
	class USpringArmComponent *SpringArmComp_;
	class UCameraComponent *CameraComp_;

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

	void InitComp(class UCameraComponent* CameraComp , class USpringArmComponent* SpringArm, float ArmSpringDistance );

	bool ExecToggle = false;

	bool CurrentToggle = false;

	void ToggleButton ( bool ChangeToggle );

	void InZooming ( float DetaTIme );
	
	void OutZooming ( float DetaTIme );
	
	void CameraZoomInMoving ( float DetaTime );
	
	void CameraZoomOutMoving ( float DetaTime );
};
