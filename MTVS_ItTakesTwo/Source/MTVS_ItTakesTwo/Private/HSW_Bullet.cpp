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

	//�浹ü
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetCollisionProfileName(TEXT("BlockAll"));

	//����
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//�߻�ü
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->SetUpdatedComponent(RootComponent);
}

// Called when the game starts or when spawned
void AHSW_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHSW_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

