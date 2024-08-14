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
		//UE_LOG ( LogTemp , Log , TEXT ( "Socket Transform: %s" ) , *t.ToString ( ) );

		auto* nail = GetWorld ( )->SpawnActor<AHSW_Bullet> ( BulletFactory ,params );

		if ( nail )
		{
			Magazine.Add ( nail );
			nail->SetNailBag(this );
			nail->NailBasic();
		}
		else 
		{
			GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Nail Not Spawned" ) );
		}

		
	}

	SocketIndex = 2;
}

// Called every frame
void AHSW_BulletManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//못통에서 못을 꺼낸다.
AHSW_Bullet* AHSW_BulletManager::NailPop ( FVector v , FRotator r )
{
	if ( Magazine.IsEmpty ( ) == true )
	{
		UE_LOG( LogTemp , Warning , TEXT ( "NailPush : NailInven_Out is Empty" ) );
		return nullptr;
	}
	AHSW_Bullet* nail = Magazine.Pop ( );
	Magazine_Out.Push ( nail );
	//GrabbedNail = nail;
	return nail;
}

AHSW_Bullet* AHSW_BulletManager::NailPush ( )
{
	if ( Magazine_Out.IsEmpty ( ) == true )
	{
		UE_LOG ( LogTemp , Warning , TEXT ( "NailPush : NailInven_Out is Empty" ) );
		return nullptr;
	}
	AHSW_Bullet* nail = Magazine_Out.Pop ( );
	if ( nail == nullptr )
	{
		return nullptr;
	}
	Magazine.Push ( nail );
	return nail;
		// 		// Nail이 들어갈 소켓 이름을 가져온다.
		// 		FString socketNameString = FString::Printf ( TEXT ( "NailBag_%d" ) , Magazine.Num ( )-1);
		// 		//FString DebugMsg = FString::Printf ( TEXT ( "%d" ) , Magazine.Num() );
		// 		//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , DebugMsg);
		// 		FName socketName ( *socketNameString );
		// 		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , socketNameString );
		// 		// 해당 소켓이름에 맞는 곳에 attach 한다.
		// 		nail->AttachToActor ( this , FAttachmentTransformRules::KeepRelativeTransform, socketName );
		// 		FTransform t = this->MeshComp->GetSocketTransform ( socketName );
		// 		nail->SetActorLocation ( t.GetLocation ( ) );
		// 		nail->SetActorRotation ( t.GetRotation ( ) );

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