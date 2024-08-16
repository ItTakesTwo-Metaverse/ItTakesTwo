// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSR_MayUseHammerObj.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MTVS_ITTAKESTWO_API UCSR_MayUseHammerObj : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSR_MayUseHammerObj();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModifyAble" )
	TSubclassOf<class AHSW_Hammer> HammerFactory;

	UPROPERTY (EditDefaultsOnly )
	class AHSW_Hammer *Hammer;

	UPROPERTY (EditDefaultsOnly )
	class ACSR_Player_May *MayPlayer;
	void Attack( );
		
	void DetachHammer ( );
	void AttachHammer ( );



};
