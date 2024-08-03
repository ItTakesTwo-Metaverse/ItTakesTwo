// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RightArmAnim.generated.h"

UENUM ( BlueprintType )
enum class ERightAnimState : uint8
{
	//Start,
	Idle,
	Attack1,
	Attack2,
	Attack3,
	Attack4,
	Attack5,
	CoolDown,
	Die
};


/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API URightArmAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	URightArmAnim( );

	virtual void NativeInitializeAnimation () override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void SetAnimState( ERightAnimState NewState);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ERightAnimState AnimState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsAttacking;

	//UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite )
	//class UAnimMontage* IdleMontage;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadWrite )
	class UAnimMontage* Attack1Montage;

private:
	FOnMontageEnded MontageEndedDelegate;

	UFUNCTION( )
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted );


};
