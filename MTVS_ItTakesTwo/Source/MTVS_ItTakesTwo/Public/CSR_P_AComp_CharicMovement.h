// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "CSR_P_AComp_CharicMovement.generated.h"

const int32 DONTMOVE = 0;
const int32 NORMALEMOVE = 1;
const int32 JUMPMOVEE = 2;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MTVS_ITTAKESTWO_API UCSR_P_AComp_CharicMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSR_P_AComp_CharicMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY( BlueprintReadOnly )
	class ACSR_P_Player * Character_;

	UPROPERTY(EditDefaultsOnly)
	class UCharacterMovementComponent * CharacterStateComp;

	// 초기에 이동 관련 상수값들을 초기화 해준다.
	void Setting ();

	// 패드, 키보드 의 X,Y축 입력값을 저장한다.
	UPROPERTY(BlueprintReadOnly)
	FVector2D PadDirection;

	// 8방향 중 더 근접한 것에 접근한다.
	UPROPERTY(BlueprintReadOnly)
	FVector ChoosedDirection;

	// 앞, 좌 이동 값을 더한 값
	UPROPERTY(BlueprintReadOnly)
	float AbsScale = 0.0f;

	UPROPERTY( BlueprintReadOnly )
	float Acceleration = 0;

	// 플레이어의 이동속도 상수값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	float Speed = 600.0f;

	// AbsScale이 밑의 값보다 낮으면 움직이지 않는다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	float StickSensitivity_NoInput = 0.3f;
	
	// AbsScale이 밑의 값보다 낮으면 느리게 움직인다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	float StickSensitivity_WeakInput = 0.85f;
	
	// 현재 이동 상태
	int32 MoveFlag = DONTMOVE;

	// 이동 입력에 따라 플레이어를 이동시키기 위한 함수 - 현재 상태에 따라 이동 방식이 달라진다.
	void PlayerMoveSelect(const FInputActionValue& Value);

	// 8 방향 중 어느방향으로 갈지를 저장하고 있는 값.
	int32  ChooseDirectionFlag ( FVector2D &Direction );

	// 카메라의 정면 벡터를 캐릭터의 정면 벡터라고 했을 때 캐릭터의 방향벡터.
	void CaracterDirection ( int32 flag );

	FVector JumpInitDirection;

	void InitSecondJump( );

	bool SecondJump = false;

	void RunStart( const FInputActionValue& Value );

	void RunEnd ( const FInputActionValue& Value );
};
