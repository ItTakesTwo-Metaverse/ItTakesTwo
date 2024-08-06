// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSW_Hammer.generated.h"

UCLASS()
class MTVS_ITTAKESTWO_API AHSW_Hammer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHSW_Hammer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;
	
	//UPROPERTY(EditAnywhere,BlueprintReadWrite)
	//class USkeletalMeshComponent* HammerMesh;

	UFUNCTION ( )
	void OnMyBoxHit ( UPrimitiveComponent* HitComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit );

	//Overlap이 작동할 함수
	UFUNCTION()
	void OnMyBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnMyBoxEndOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex);


	UPROPERTY ()
	class AHSW_Bullet* Nail;

	bool bCanHanging;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite )
	bool bIsHanging;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite )
	class AHSW_Bullet* bullet;

	UFUNCTION ( BlueprintCallable)
	void AttachHammerToNail ( );
	UFUNCTION ( BlueprintCallable )
	void DetachHammerFromNail ( );

};
