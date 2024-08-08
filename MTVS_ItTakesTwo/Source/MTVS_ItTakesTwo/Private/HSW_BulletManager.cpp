// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_BulletManager.h"
#include "HSW_Bullet.h"

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
		auto* nail = GetWorld ( )->SpawnActor<AHSW_Bullet> ( BulletFactory , params );

		nail->SetActive ( false );
		Magazine.Add ( nail );
	}
	
}

// Called every frame
void AHSW_BulletManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AHSW_Bullet* AHSW_BulletManager::NailPop ( FVector v , FRotator r )
{
	if ( Magazine.IsEmpty ( ) == true )
	{
		UE_LOG( LogTemp , Warning , TEXT ( "NailPush : NailInven_Out is Empty" ) );
		return nullptr;
	}
	AHSW_Bullet* nail = Magazine.Pop ( );
	nail->SetActive ( true );
	Magazine_Out.Push ( nail );
	nail->SetActorLocationAndRotation ( v , r );
	return nail;
}

void AHSW_BulletManager::NailPush ( AHSW_Bullet* Nail )
{
	if ( Magazine_Out.IsEmpty ( ) == true )
	{
		UE_LOG ( LogTemp , Warning , TEXT ( "NailPush : NailInven_Out is Empty" ) );
		return;
	}
	AHSW_Bullet* nail = Magazine_Out.Pop ( );
	if ( nail != nullptr )
	{
		nail->SetState ( ENailState::RETURNING );
		Magazine.Push ( nail );
	}
}

