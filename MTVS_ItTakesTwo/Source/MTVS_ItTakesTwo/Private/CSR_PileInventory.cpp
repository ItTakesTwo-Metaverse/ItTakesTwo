// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_PileInventory.h"
#include "HSW_Bullet.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UCSR_PileInventory::UCSR_PileInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
}


// Called when the game starts
void UCSR_PileInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	NailSponAuto ( );
	
}


// Called every frame
void UCSR_PileInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCSR_PileInventory::NailSponAuto ( )
{
	UE_LOG ( LogTemp , Warning , TEXT ( "NailSponAuto" ) );
	FActorSpawnParameters parms;
	parms.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for ( int i = 0; i < 3; i++ ) {
		NailInven.Push ( this->GetWorld ( )->SpawnActor<AHSW_Bullet> ( NailFactory, parms ) );
		SetVisibleOff( NailInven[i] );
	}
}

void UCSR_PileInventory::SetVisibleOff ( AHSW_Bullet *Nail )
{
	Nail->BoxComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
	Nail->MeshComp->SetVisibility ( false );
}

void UCSR_PileInventory::SetVisibleOn ( AHSW_Bullet* Nail )
{
	Nail->BoxComp->SetCollisionEnabled ( ECollisionEnabled::QueryAndPhysics );
	Nail->MeshComp->SetVisibility ( true );
}

//
AHSW_Bullet *UCSR_PileInventory::NailPop (FVector v , FRotator r )
{
	if ( NailInven.IsEmpty ( ) == true ) {
		UE_LOG ( LogTemp , Warning , TEXT ( "NailPush : NailInven is Empty" ) );
		return nullptr;
	}
	AHSW_Bullet* Nail = NailInven.Pop ( );
	SetVisibleOn ( Nail );
	NailInven_Out.Push ( Nail );
	Nail->SetActorLocationAndRotation ( v , r );
	return (Nail);
}

void UCSR_PileInventory::NailPush (AHSW_Bullet* Nail )
{
	if ( NailInven_Out.IsEmpty ( ) == true ) {
		UE_LOG(LogTemp, Warning, TEXT("NailPush : NailInven_Out is Empty" ));
		return ;
	}
	AHSW_Bullet* Naill = NailInven_Out.Pop ( );
	if ( Naill != nullptr ) {
		Naill->SetState ( ENailState::RETURNING );
		NailInven.Push ( Naill );
	}
}

