// Fill out your copyright notice in the Description page of Project Settings.


#include "BossNailSpawner.h"
#include "BossNail.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABossNailSpawner::ABossNailSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent> ( TEXT ( "ROOT" ) );
	SetRootComponent ( RootComp );


}

// Called when the game starts or when spawned
void ABossNailSpawner::BeginPlay()
{
	Super::BeginPlay();

	Player1 = GetWorld ( )->GetFirstPlayerController ( )->GetPawn ( );
	APlayerController* SecondPlayerController = UGameplayStatics::GetPlayerController ( GetWorld ( ) , 1 );
	Player2 = SecondPlayerController->GetPawn ( );
}

// Called every frame
void ABossNailSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossNailSpawner::PlayNailAttack ( )
{

}

void ABossNailSpawner::DropNail ( )
{
	FVector CharacterLocation = Player1->GetActorLocation ( );

	for ( int32 i = 0; i < NailMaxCount; i++ )
	{

		// 랜덤한 위치 생성
		FVector SpawnLocation = CharacterLocation + FMath::VRand ( ) * 100.f;

		// 총알 스폰
		GetWorld ( )->SpawnActor<ABossNail> ( NailFactory , SpawnLocation,FRotator::ZeroRotator );
	}
}

