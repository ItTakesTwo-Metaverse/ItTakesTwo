// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_Hammer.h"
#include "Components/BoxComponent.h"
#include "../Public/HSW_Bullet.h"

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

	//스켈레탈메시
	//HammerMesh = CreateDefaultSubobject<USkeletalMeshComponent> (TEXT ( "HammerMesh" ) );
	//HammerMesh->SetupAttachment(RootComponent);
	//HammerMesh->SetCollisionProfileName ( TEXT ( "Hammer" ) );

}

// Called when the game starts or when spawned
void AHSW_Hammer::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentHit.AddDynamic( this , &AHSW_Hammer::OnMyBoxHit );
	BoxComp->OnComponentBeginOverlap.AddDynamic ( this , &AHSW_Hammer::OnMyBoxBeginOverlap );
	BoxComp->OnComponentEndOverlap.AddDynamic ( this , &AHSW_Hammer::OnMyBoxEndOverlap );
}

// Called every frame
void AHSW_Hammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ( bIsHanging )
	{
		//SetActorLocation ( Nail->GetActorLocation ( ) );
		//Nail ->	Socket 
		//player -> socket -> hammer
		//SceneComponent
		//this->AttachToActor ( Nail );
	}

}

void AHSW_Hammer::OnMyBoxHit ( UPrimitiveComponent* HitComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit )
{
	bullet = Cast<AHSW_Bullet> ( OtherActor );
//	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Hammer" ) );
	if ( bullet )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "Hammer and nail" ) );
	}
}

void AHSW_Hammer::OnMyBoxBeginOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	bullet = Cast<AHSW_Bullet> ( OtherActor );
	if ( bullet )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "Begin Overlap" ) );
		bCanHanging = true;
	}
}

void AHSW_Hammer::OnMyBoxEndOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex )
{
	if ( bullet )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "End Overlap" ) );
		bCanHanging = false;

	}
}

void AHSW_Hammer::AttachHammerToNail ( )
{
	if ( bCanHanging )
	{
		bIsHanging = true;
		MeshComp->AttachToComponent ( bullet->MeshComp , FAttachmentTransformRules::KeepRelativeTransform , TEXT ( "AttachingPoint" ) );
	}
}

void AHSW_Hammer::DetachHammerFromNail ( )
{
	bIsHanging = false;
}
