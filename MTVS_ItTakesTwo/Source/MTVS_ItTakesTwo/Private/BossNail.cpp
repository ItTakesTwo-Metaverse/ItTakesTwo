// Fill out your copyright notice in the Description page of Project Settings.


#include "BossNail.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABossNail::ABossNail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent> ( TEXT ( "BoxComp" ) );
	SetRootComponent ( BoxComp );
	BoxComp->SetBoxExtent ( FVector (5.238329 , 5.357734 , 30.542622 ) );

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "MeshComp" ) );
	MeshComp->SetupAttachment ( BoxComp );
	MeshComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
}

// Called when the game starts or when spawned
void ABossNail::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ABossNail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ( bShoot )
	{
		Shoot ( DeltaTime );
	}
	
}

void ABossNail::SetActive ( bool bValue )
{

	// 만약 bValue가 true라면 보이고, 충돌체 활성화 하고싶다.
	MeshComp->SetVisibility ( bValue );
	//cf. MeshComp->GetVisibeFlag();
	if ( bValue )
	{
		bShoot = true;
		BoxComp->SetCollisionEnabled ( ECollisionEnabled::QueryAndPhysics);
	}
	// 그렇지 않다면, 안보이고, 충돌체 비활성화 하고싶다.
	else
	{
		bShoot = false;
		BoxComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
	}
}

void ABossNail::Shoot ( float DeltaTime )
{
	Dir = GetActorForwardVector ( );
	SetActorLocation ( GetActorLocation ( ) + (Dir * Speed * DeltaTime));

}

