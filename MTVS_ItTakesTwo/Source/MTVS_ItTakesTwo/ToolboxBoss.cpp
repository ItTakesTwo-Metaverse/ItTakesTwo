// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolboxBoss.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AToolboxBoss::AToolboxBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// ���� ��ü

	//BossMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BossMesh"));
	GetMesh()->SetupAttachment(RootComponent);
	GetMesh()->SetRelativeLocation(FVector(0, 0, 450));
	GetMesh()->SetRelativeScale3D(FVector(5, 10, 10));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BossMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'"));
	if (BossMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BossMeshAsset.Object);
	}

	// ���� ����
	LeftArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftArmMesh"));
	LeftArmMesh->SetupAttachment(GetMesh(), TEXT("LeftArmSocket"));
	LeftArmMesh->SetRelativeLocation(FVector(0,-12,20));
	LeftArmMesh->SetRelativeRotation(FRotator(-10, 90, -90));
	LeftArmMesh->SetRelativeScale3D(FVector(0.05,0.3,0.05));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LeftArmMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
	if (LeftArmMeshAsset.Succeeded())
	{
		LeftArmMesh->SetSkeletalMesh(LeftArmMeshAsset.Object);
	}

	// ���� ������
	RightArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightArmMesh"));
	RightArmMesh->SetupAttachment(GetMesh(), TEXT("RightArmSocket"));
	RightArmMesh->SetRelativeLocation(FVector(0, 12, 20));
	RightArmMesh->SetRelativeRotation(FRotator(-10, 270, -90));
	RightArmMesh->SetRelativeScale3D(FVector(0.05, 0.3, 0.05));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RightArmMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
	if (RightArmMeshAsset.Succeeded())
	{
		RightArmMesh->SetSkeletalMesh(RightArmMeshAsset.Object);
	}

	// ���� ������
	RightHandBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHandBox"));
	RightHandBox->SetupAttachment(RightArmMesh, TEXT("RightHandSocket"));
	RightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHandMesh"));
	RightHandMesh->SetupAttachment(RightHandBox);
	RightHandBox->SetRelativeLocation(FVector(0, 0, -240));
	RightHandBox->SetRelativeRotation(FRotator(0, 0, -90));


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

