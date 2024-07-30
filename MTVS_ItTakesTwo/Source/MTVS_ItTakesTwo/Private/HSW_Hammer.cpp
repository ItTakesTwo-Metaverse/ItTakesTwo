// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_Hammer.h"
#include "Components/BoxComponent.h"

// Sets default values
AHSW_Hammer::AHSW_Hammer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//충돌체
	BoxComp = CreateDefaultSubobject<UBoxComponent> ( TEXT ( "BoxComp" ) );
	SetRootComponent ( BoxComp );
	BoxComp->SetCollisionProfileName ( TEXT ( "Hammer" ) );

	//외형
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "MeshComp" ) );
	MeshComp->SetupAttachment ( RootComponent );
	MeshComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
}

// Called when the game starts or when spawned
void AHSW_Hammer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHSW_Hammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

