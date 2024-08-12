// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSR_P_AComp_InputBInd.h"
#include "CSR_C_AComp_InputBIndCody.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API UCSR_C_AComp_InputBIndCody : public UCSR_P_AComp_InputBInd
{
	GENERATED_BODY()
public:
	virtual void BeginPlay ( ) override;

	virtual void SetupInputComponent ( class UEnhancedInputComponent* InputKey ) override;

	UPROPERTY (  )
	class ACSR_Player_Cody *CodyCharacter_;

	UPROPERTY( )
	class AHSW_BulletManager* NailBag;

	// 조준
	UPROPERTY(EditDefaultsOnly, Category = "ModifyAble" )
	class UInputAction	*IA_CPile_;

	//못 발사
	UPROPERTY ( EditDefaultsOnly, Category = "ModifyAble" )
	class UInputAction* IA_CFire;

    // 못 회수할 IA, 함수
    UPROPERTY(EditDefaultsOnly, Category = "ModifyAble" )
    class UInputAction* IA_CBack;

	void ChangeZoomIn ( );

	void ChangeZoomOut( );

	void ExecFIre( );

	void ExecBack();

	UPROPERTY ( EditDefaultsOnly)
	AHSW_Bullet* Nail;
};
