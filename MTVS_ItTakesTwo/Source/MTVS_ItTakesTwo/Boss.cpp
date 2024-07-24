// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BossBoxcomp = CreateDefaultSubobject<UBoxComponent>(TEXT("BossBoxcomp"));
	SetRootComponent(BossBoxcomp);
	
	BossMeshcomp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BossMeshcomp"));
	BossMeshcomp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

