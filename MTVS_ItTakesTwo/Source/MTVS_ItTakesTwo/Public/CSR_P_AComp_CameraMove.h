// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "CSR_P_AComp_CameraMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MTVS_ITTAKESTWO_API UCSR_P_AComp_CameraMove : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSR_P_AComp_CameraMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// owner 캐릭터
	UPROPERTY( BlueprintReadOnly )
	class ACSR_P_Player *Character_;

	// 캐릭터 이동 컴포넌트
	UPROPERTY(EditDefaultsOnly)
	class UCharacterMovementComponent * CharacterStateComp;

	// 보는 곳을 저장하고 있다.
	FVector2D view;

	// 뷰 입력에 따라 플레이어의 카메라암을 회전시킨다.
	void Player_View ( const FInputActionValue& Value );
};
