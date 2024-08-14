// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSW_BulletManager.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API AHSW_BulletManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHSW_BulletManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite )
	class UStaticMeshComponent* MeshComp;

	UPROPERTY ( )
	class AHSW_Bullet* Bullet;
	UPROPERTY ( )
	class AHSW_Bullet* GrabbedNail;
	UPROPERTY ( )
	TArray<class AHSW_Bullet*> Magazine;
	UPROPERTY ( )
	TArray<class AHSW_Bullet*> Magazine_Out;

	UPROPERTY(EditAnywhere )
	TSubclassOf<class AHSW_Bullet> BulletFactory;

	UFUNCTION(BlueprintCallable )
	AHSW_Bullet* NailPop ( FVector v , FRotator r);
	UFUNCTION(BlueprintCallable )
	AHSW_Bullet* NailPush ( );

	int32 SocketIndex;

	FVector GetNailBagSocketLocation ( );
	FRotator GetNailBagSocketRotation ( );
};
