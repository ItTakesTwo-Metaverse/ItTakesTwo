// Fill out your copyright notice in the Description page of Project Settings.


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
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , SocketNameString );

		FTransform t = this->MeshComp->GetSocketTransform ( SocketName );
		//UE_LOG ( LogTemp , Log , TEXT ( "Socket Transform: %s" ) , *t.ToString ( ) );

		Nail = GetWorld ( )->SpawnActor<AHSW_Bullet> ( BulletFactory , params );

		if ( Nail )
		{
			Nail->SetNailBag ( this );
			Magazine.Add ( Nail );
			Nail->SetSocketName ( );
			Nail->AttachToActor ( this , FAttachmentTransformRules::KeepRelativeTransform , SocketName );
		}
		else
		{
			GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Nail Not Spawned" ) );
		}
	}
	//GetWorld ( )->GetTimerManager ( ).SetTimer ( TimerHandle , this , &AHSW_BulletManager::NailSetting , 0.4f , false );

}

// Called every frame
void AHSW_BulletManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//못통에서 못을 꺼낸다.
AHSW_Bullet* AHSW_BulletManager::NailPop ( )
{
	if ( Magazine.IsEmpty ( ) == true )
	{
		UE_LOG( LogTemp , Warning , TEXT ( "NailPush : NailInven_Out is Empty" ) );
		return nullptr;
	}

	Nail = Magazine.Pop ( );
	//Magazine_Out.Push ( Nail );
	return Nail;
}

void AHSW_BulletManager::NailPush ( AHSW_Bullet* currentNail )
{
	if ( Magazine.Num() > 3 )
	{
		UE_LOG ( LogTemp , Warning , TEXT ( "Nail Full" ) );
		return;
	}
	if ( currentNail != nullptr )
	{
		Magazine.Push ( Nail );
	}
}

void AHSW_BulletManager::NailSetting ( )
{

}

AHSW_Bullet* AHSW_BulletManager::NailOutPop ( )
{
	if ( Magazine_Out.IsEmpty ( ) == true )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ("NailOutPop : Magazine_Out is Empty"  ) );
		return nullptr;
	}

	auto* nail = Magazine_Out.Pop ( );
	return nail;
}

void AHSW_BulletManager::NailOutPush ( AHSW_Bullet* EmbeddedNail )
{
	if ( Magazine_Out.Num ( ) > 3 )
	{
		UE_LOG ( LogTemp , Warning , TEXT ( "Nail_Out Full" ) );
		return;
	}
	if ( EmbeddedNail != nullptr )
	{
		Magazine_Out.Push ( EmbeddedNail );
	}
}

