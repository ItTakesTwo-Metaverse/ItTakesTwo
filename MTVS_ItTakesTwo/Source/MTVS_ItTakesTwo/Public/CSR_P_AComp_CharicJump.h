// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSR_P_AComp_CharicJump.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MTVS_ITTAKESTWO_API UCSR_P_AComp_CharicJump : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSR_P_AComp_CharicJump();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY( BlueprintReadOnly )
	class ACSR_P_Player *Character_;

	UPROPERTY(EditDefaultsOnly)
	class UCharacterMovementComponent *CharacterStateComp;

	// 현재 하늘에 있는지 나타냄
	UPROPERTY(BlueprintReadOnly)
	bool IntheSky = false;

	// 세컨트 점프가 가능한지 나타냄
	UPROPERTY( BlueprintReadOnly)
	bool SecondJumpPossible = true;

	// 첫 점프의 최대값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	float FirstJumpZVelocity = 600;

	// 두 번째 점프의 최대값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	float SecondJumpZVelocity = 600;

	// 최대 점프에 머무는 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	float JumpMaxHoldT = 0.01;
	
	// 필요값들 초기 init
	void Setting ();

	// 점프를 발생 시키는 함수
	void PlayerJump ( const FInputActionValue& Value );

	void Landed ( );
};
