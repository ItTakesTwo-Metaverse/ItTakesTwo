// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_BulletManager.h"

// Sets default values
AHSW_BulletManager::AHSW_BulletManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHSW_BulletManager::BeginPlay()
{
	Super::BeginPlay();
	for ( int32 i = 0; i < 3; i++ )
	{
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		auto* bullet = GetWorld ( )->SpawnActor<AHSW_Bullet> ( BulletFactory , params );
	}
	
}

// Called every frame
void AHSW_BulletManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

