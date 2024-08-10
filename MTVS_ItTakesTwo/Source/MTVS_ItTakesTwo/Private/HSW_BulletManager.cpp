﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_BulletManager.h"
#include "HSW_Bullet.h"

// Sets default values
AHSW_BulletManager::AHSW_BulletManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "MeshComp" ) );
	SetRootComponent ( MeshComp );
	MeshComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );

}

// Called when the game starts or when spawned
void AHSW_BulletManager::BeginPlay()
{
	Super::BeginPlay();
	for ( int32 i = 0; i < 3; i++ )
	{
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FString SocketNameString = FString::Printf ( TEXT ( "NailBag_%d" ) , i );
		FName SocketName ( *SocketNameString );

		FTransform t = this->MeshComp->GetSocketTransform ( SocketName );
		UE_LOG ( LogTemp , Log , TEXT ( "Socket Transform: %s" ) , *t.ToString ( ) );

		auto* nail = GetWorld ( )->SpawnActor<AHSW_Bullet> ( BulletFactory , t,params );

		if ( nail )
		{
		nail->AttachToActor ( this , FAttachmentTransformRules::SnapToTargetIncludingScale );
		nail->SetActorLocation ( t.GetLocation ( ) );
		nail->SetActorRotation ( t.GetRotation ( ) );
			Magazine.Add ( nail );
		}
		else 
		{
			GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Nail Not Spawned" ) );
		}

		
	}

	SocketIndex = 0;
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
	nail->NailReadytoShoot ( v , r );
	Magazine_Out.Push ( nail );
	return nail;
}

void AHSW_BulletManager::NailPush ( FVector v , FRotator r )
{
	if ( Magazine_Out.IsEmpty ( ) == true )
	{
		UE_LOG ( LogTemp , Warning , TEXT ( "NailPush : NailInven_Out is Empty" ) );
		return;
	}

	AHSW_Bullet* nail = Magazine_Out.Pop ( );
	SocketIndex = Magazine.Num();
	if ( nail != nullptr )
	{
		nail->SetState ( ENailState::RETURNING );
		Magazine.Push ( nail );
	}
}

FVector AHSW_BulletManager::GetNailBagSocketLocation ( )
{
	FString SocketNameString = FString::Printf ( TEXT ( "NailBag_%d" ) , SocketIndex );
	FName SocketName ( *SocketNameString );
	return MeshComp->GetSocketLocation ( SocketName );
}

FRotator AHSW_BulletManager::GetNailBagSocketRotation ( )
{
	FString SocketNameString = FString::Printf ( TEXT ( "NailBag_%d" ) , SocketIndex );
	FName SocketName ( *SocketNameString );
	return MeshComp->GetSocketRotation ( SocketName );
}