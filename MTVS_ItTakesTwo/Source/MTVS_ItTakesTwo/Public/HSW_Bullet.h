// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSW_BulletManager.h"
#include "HSW_Bullet.generated.h"

UENUM(BlueprintType)
enum class ENailState: uint8
{
	BASIC		UMETA ( DisplayName = "기본" ) ,
	LOAD		UMETA (DisplyaName ="장전" ),
	SHOOT		UMETA ( DisplayName = "날라가기" ),
	EMBEDDED	UMETA ( DisplayName = "박힘" ) ,
	UNEMBEDDED	UMETA ( DisplayName = "박기실패" ) ,
	RETURNING	UMETA ( DisplayName = "돌아옴" ) ,
	GOTOBAG		UMETA ( DisplayName = "가방으로" ),
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
	void TickLoad ( const float& DeltaTime );
	void TickShoot ( const float& DeltaTime );
	void TickEmbedded ( const float& DeltaTime );
	void TickUnembedded ( const float& DeltaTime );

	UFUNCTION(BlueprintCallable)
	void TickReturning ( const float& DeltaTime );
	void TickGoToBag ( const float& DeltaTime );
	

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly )
	ENailState State = ENailState::BASIC;

	float NailDefaultDist = 100;

	//유도탄
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly )
	TWeakObjectPtr<USceneComponent> NailHomingTargetComponent;

	void SetState( ENailState NextState );

	FVector StartPoint;
	FVector EndPoint;
	float Distance;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly )
	float Speed = 10000;

	void SetActive ( bool bValue );

	FVector nailDestLocation;
	FRotator nailDestRotation;

	void SetNailReturnDestination ( );

	void NailReadytoShoot ( FVector v , FRotator r );

	void SetSocketName();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class AHSW_BulletManager* NailBag;
	void SetNailBag ( AHSW_BulletManager* nailBag );

	UPROPERTY (  )
	class ACSR_Player_Cody* Player;
	//class APawn* Player;

	UFUNCTION(BlueprintCallable )
	void NailBasic( );
	UFUNCTION(BlueprintCallable )
	void NailShoot ( );
	UFUNCTION(BlueprintCallable )
	void NailLoad ( );
	UFUNCTION(BlueprintCallable )
	void NailReturn( );

	void NailEmbedded ( );
	
	void LoadSecondPlayer ( );

	FTimerHandle TimerHandle;

	FTransform SocketTransform;

	FName SocketName;

	UPROPERTY( )
	UPrimitiveComponent* TargetComp;

	bool bIsLoading;
	bool bIsShooting;
	bool bBasic;
	bool bIsReturning;

	float CurrentTime = 0.f;
	UPROPERTY(EditDefaultsOnly )
	float BackTime = 3.f;

	void SetbIsReturning ( bool value );

	void FirstAttach ( FTransform t);
	void SetStartAndEnd ( FVector start , FVector end );

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCameraShakeBase> NailShootCameraShake;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCameraShakeBase> NailReturnCameraShake;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* NailLoadSFV;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* NailEmbeddedSFV;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* NailUnEmbeddedSFV;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* NailReturnSFV;

	FVector ReturnDir;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* NailEmbeddedVFXFactory;


};