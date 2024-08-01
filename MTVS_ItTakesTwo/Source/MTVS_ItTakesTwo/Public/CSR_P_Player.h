﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "CSR_P_Player.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API ACSR_P_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACSR_P_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	int State = 0;

#pragma region
	// 플레이어 카메라 셋팅
	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent *SpringArmComp;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent *CameraComp;

	UPROPERTY ( EditAnywhere , BlueprintReadWrite, Category="ModifyAble" )
	float EarlyCameraDistance = 1000;

	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "ModifyAble" )
	float EarlyCameraArmRotateHeight = 20;
	
#pragma endregion ComponentSetting

#pragma region
	UPROPERTY(EditDefaultsOnly, Category = "ModifyAble" )
	class UInputMappingContext *IMC_PlayerController_;

	UPROPERTY(EditDefaultsOnly, Category = "ModifyAble" )
	class UInputAction	*Move_;

	UPROPERTY(EditDefaultsOnly, Category = "ModifyAble" )
	class UInputAction	*Look_;

#pragma endregion KeyBind

#pragma region
	
	// 패드, 키보드 의 X,Y축 입력값을 저장한다.
	UPROPERTY(BlueprintReadOnly)
	FVector2D PadDirection;

	// 8방향 중 더 근접한 것에 접근한다.
	UPROPERTY(BlueprintReadOnly)
	FVector ChoosedDirection;

	// 이동 입력값 중 절대값이 큰 값을 저장한다.
	UPROPERTY(BlueprintReadOnly)
	float AbsScale = 0.0f;

	// 플레이어의 이동속도의 곱하기 상수값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	float Speed = 1.0f;

	// AbsScale이 밑의 값보다 낮으면 움직이지 않는다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	float StickSensitivity_NoInput = 0.5f;
	
	// AbsScale이 밑의 값보다 낮으면 느리게 움직인다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	float StickSensitivity_WeakInput = 0.9f;

	// 이동 입력에 따라 플레이어를 이동시키기 위한 값을 설정하는 함수
	void Player_Move(const FInputActionValue& Value);

	// 8 방향 중 어느방향으로 갈지를 저장하고 있는 값.
	int32  ChooseDirectionFlag ( FVector2D &Direction );

	// 카메라의 정면 벡터를 캐릭터의 정면 벡터라고 했을 때 캐릭터의 방향벡터.
	void CaracterDirection ( int32 flag );
#pragma endregion PlayerMove

#pragma region
	// 보는 곳을 저장하고 있다.
	FVector2D view;

	// 뷰 입력에 따라 플레이어의 카메라암을 회전시킨다.
	void Player_View( const FInputActionValue& Value );
#pragma endregion PlayerView
};
