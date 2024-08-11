// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSR_BaseAnimation.h"
#include "CSR_CodyAnimation.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API UCSR_CodyAnimation : public UCSR_BaseAnimation
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation ( ) override;

	virtual void NativeUpdateAnimation ( float DeltaSeconds ) override;

	UPROPERTY ( EditDefaultsOnly )
	class ACSR_Player_Cody* Player;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Speed = 0;
	
	// Horizontal
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Direction = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsInAir =false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsCrouched = false;

//// 앞 뒤 속도
//this->Speed = FVector::DotProduct ( forwardVector , velocity );

//FVector rightVector = Player->GetActorRightVector ( );

//// 좌, 우 속도
//this->Direction

};
