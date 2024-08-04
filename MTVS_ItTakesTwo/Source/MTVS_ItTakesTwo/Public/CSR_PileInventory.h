// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSR_PileInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MTVS_ITTAKESTWO_API UCSR_PileInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSR_PileInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY ( EditAnywhere , Category = "ModifyAble" )
	TSubclassOf<class AHSW_Bullet> NailFactory;

	TArray<class AHSW_Bullet *> NailInven;

	TArray<class AHSW_Bullet*> NailInven_Out;


	void NailSponAuto ( );

	void SetVisibleOff( AHSW_Bullet* Nail );

	void SetVisibleOn( AHSW_Bullet* Nail );

	class AHSW_Bullet *NailPop ( FVector v , FRotator r );

	void NailPush (class AHSW_Bullet *Nail );
};
