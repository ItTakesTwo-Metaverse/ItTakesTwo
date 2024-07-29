// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AHSW_Bullet::AHSW_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//충돌체
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetCollisionProfileName(TEXT("BlockAll"));

	//외형
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//발사체
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->SetUpdatedComponent(RootComponent);
}

// Called when the game starts or when spawned
void AHSW_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentHit.AddDynamic( this , &AHSW_Bullet::OnMyWallHit );
}

// Called every frame
void AHSW_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ( bRetunring )
	{
		ReturnToPlayer ( );
	}

}

void AHSW_Bullet::OnMyWallHit ( UPrimitiveComponent* HitComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit )
{
	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Red , TEXT ( "collision" ) );
	if ( OtherActor->ActorHasTag ( TEXT ( "Wall1" ) ) )
	{
		MovementComp->bShouldBounce = false;
	}
	else if ( OtherActor->ActorHasTag ( TEXT ( "Wall2" ) ) )
	{
		MovementComp->bShouldBounce = true;
	}
}

void AHSW_Bullet::ReturnToPlayer ( )
{
	//GetActorLocation() =
}


