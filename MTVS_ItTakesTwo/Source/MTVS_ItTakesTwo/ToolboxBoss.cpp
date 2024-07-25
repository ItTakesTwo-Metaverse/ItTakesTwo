// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolboxBoss.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AToolboxBoss::AToolboxBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// º¸½º ¸öÃ¼
	BossMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BossMesh"));
	BossMesh->SetupAttachment(RootComponent);
	BossMesh->SetRelativeScale3D(FVector(2.5, 5, 5));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BossMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'"));
	if (BossMeshAsset.Succeeded())
	{
		BossMesh->SetSkeletalMesh(BossMeshAsset.Object);
	}

	// º¸½º ¿ÞÆÈ
	LeftArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftArmMesh"));
	LeftArmMesh->SetupAttachment(BossMesh, TEXT("LeftArmSocket"));
	LeftArmMesh->SetRelativeLocation(FVector(8,0,-12));
	LeftArmMesh->SetRelativeRotation(FRotator(80, 180, -90));
	LeftArmMesh->SetRelativeScale3D(FVector(0.05,0.3,0.05));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LeftArmMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
	if (LeftArmMeshAsset.Succeeded())
	{
		LeftArmMesh->SetSkeletalMesh(LeftArmMeshAsset.Object);
	}

	// º¸½º ¿À¸¥ÆÈ
	RightArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightArmMesh"));
	RightArmMesh->SetupAttachment(BossMesh, TEXT("RightArmSocket"));
	RightArmMesh->SetRelativeLocation(FVector(8, 0, 12));
	RightArmMesh->SetRelativeRotation(FRotator(-80, 180, 90));
	RightArmMesh->SetRelativeScale3D(FVector(0.05, 0.3, 0.05));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RightArmMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
	if (RightArmMeshAsset.Succeeded())
	{
		RightArmMesh->SetSkeletalMesh(RightArmMeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void AToolboxBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToolboxBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AToolboxBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

