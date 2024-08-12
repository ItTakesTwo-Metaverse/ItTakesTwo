// Fill out your copyright notice in the Description page of Project Settings.


#include "Wood.h"

// Sets default values
AWood::AWood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WoodCube = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "WoodCube" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WoodCubeAsset ( TEXT ( "/Script/Engine.StaticMesh'/Game/TA/wood_circle4/wood_with_circle_Cube.wood_with_circle_Cube'" ) );
	if ( WoodCubeAsset.Succeeded ( ) )
	{
		WoodCube->SetStaticMesh ( WoodCubeAsset.Object );
		WoodCube->SetupAttachment ( RootComponent );
	}

	WoodSide = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "WoodSide" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WoodSideAsset ( TEXT ( "/Script/Engine.StaticMesh'/Game/JBY/asset/tree_small/wood_side.wood_side'" ) );
	if ( WoodSideAsset.Succeeded ( ) )
	{
		WoodSide->SetStaticMesh ( WoodSideAsset.Object );
		WoodSide->SetupAttachment ( WoodCube );
		WoodSide->SetRelativeLocationAndRotation(FVector( 19.999963 , 1539.999934 , 169.999981 ), FRotator( 0, 180 , 90 ));
		WoodSide->SetRelativeScale3D(FVector(1.25,1,1));
	}

	WoodCircle1 = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "WoodCircle1" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WoodCircle1Asset ( TEXT ( "/Script/Engine.StaticMesh'/Game/TA/wood_circle4/wood_with_circle_Cylinder.wood_with_circle_Cylinder'" ) );
	if ( WoodCircle1Asset.Succeeded ( ) )
	{
		WoodCircle1->SetStaticMesh ( WoodCircle1Asset.Object );
		WoodCircle1->SetGenerateOverlapEvents ( true );
		WoodCircle1->SetCollisionProfileName ( TEXT ( "Wood" ) );
	}

	WoodCircle2 = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "WoodCircle2" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WoodCircle2Asset ( TEXT ( "/Script/Engine.StaticMesh'/Game/TA/wood_circle4/wood_with_circle_Cylinder_001.wood_with_circle_Cylinder_001'" ) );
	if ( WoodCircle2Asset.Succeeded ( ) )
	{
		WoodCircle2->SetStaticMesh ( WoodCircle2Asset.Object );
		WoodCircle2->SetGenerateOverlapEvents ( true );
		WoodCircle2->SetCollisionProfileName ( TEXT ( "Wood" ) );
	}

	WoodCircle3 = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "WoodCircle3" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WoodCircle3Asset ( TEXT ( "/Script/Engine.StaticMesh'/Game/TA/wood_circle4/wood_with_circle_Cylinder_002.wood_with_circle_Cylinder_002'" ) );
	if ( WoodCircle3Asset.Succeeded ( ) )
	{
		WoodCircle3->SetStaticMesh ( WoodCircle3Asset.Object );
		WoodCircle3->SetGenerateOverlapEvents ( true );
		WoodCircle3->SetCollisionProfileName ( TEXT ( "Wood" ) );
	}

	WoodCircle4 = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "WoodCircle4" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WoodCircle4Asset ( TEXT ( "/Script/Engine.StaticMesh'/Game/TA/wood_circle4/wood_with_circle_Cylinder_003.wood_with_circle_Cylinder_003'" ) );
	if ( WoodCircle4Asset.Succeeded ( ) )
	{
		WoodCircle4->SetStaticMesh ( WoodCircle4Asset.Object );
		WoodCircle4->SetGenerateOverlapEvents ( true );
		WoodCircle4->SetCollisionProfileName ( TEXT ( "Wood" ) );
	}
}

// Called when the game starts or when spawned
void AWood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

