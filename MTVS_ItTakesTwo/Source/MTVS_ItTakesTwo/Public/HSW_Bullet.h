// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSW_Bullet.generated.h"

UENUM(BlueprintType)
enum class ENailState: uint8
{
	BASIC		UMETA ( DisplayName = "기본" ) ,
	EMBEDDED	UMETA ( DisplayName = "박힘" ) ,
	UNEMBEDDED	UMETA ( DisplayName = "박기실패" ) ,
	RETURNING	UMETA ( DisplayName = "돌아옴" ) ,
};

UCLASS()
class MTVS_ITTAKESTWO_API AHSW_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHSW_Bullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//충돌체, 외관을 만들고싶다.
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MeshComp;

	//발사체 컴포넌트를 만들고싶다.
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* MovementComp;




//Overlap이 작동할 함수
	UFUNCTION ( )
	void OnMyWallHit ( UPrimitiveComponent* HitComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit );


	void TickBasic ( const float& DeltaTime );
	void TickEmbedded ( const float& DeltaTime );
	void TickUnembedded ( const float& DeltaTime );

	UFUNCTION(BlueprintCallable)
	void TickReturning ( const float& DeltaTime );

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly )
	ENailState State = ENailState::BASIC;

	float NailDefaultDist = 100;
};
