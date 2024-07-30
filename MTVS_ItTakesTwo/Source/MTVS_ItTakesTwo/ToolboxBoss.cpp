// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolboxBoss.h"
#include "Components/SkeletalMeshComponent.h"
#include "ToolBoxBossFSM.h"
#include "Components/SceneComponent.h"

// Sets default values
AToolboxBoss::AToolboxBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// ���� ��ü
	
	GetMesh()->SetupAttachment(RootComponent);
	GetMesh()->SetRelativeLocation(FVector(0, 0, 450));
	GetMesh()->SetRelativeScale3D(FVector(5, 10, 10));
	GetMesh()->SetCollisionProfileName(TEXT("Boss"));


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
	LeftArmMesh->SetCollisionProfileName(TEXT("Boss"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LeftArmMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
	if (LeftArmMeshAsset.Succeeded())
	{
		LeftArmMesh->SetSkeletalMesh(LeftArmMeshAsset.Object);
	}

	// ���� ������
	RightArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightArmMesh"));
	RightArmMesh->SetupAttachment(GetMesh(), TEXT("RightArmSocket"));
	RightArmMesh->SetRelativeLocationAndRotation(FVector(-5, 14.5, 18), FRotator(-90, 0, -90));
	RightArmMesh->SetRelativeScale3D(FVector(0.05, 0.05, 0.02));
	RightArmMesh->SetGenerateOverlapEvents(true);
	RightArmMesh->SetCollisionProfileName(TEXT("Boss"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RightArmMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/Meshes/SKM_RightArm.SKM_RightArm'"));
	if (RightArmMeshAsset.Succeeded())
	{
		RightArmMesh->SetSkeletalMesh(RightArmMeshAsset.Object);
	}


	// �浹ü
	RightArmMesh->OnComponentBeginOverlap.AddDynamic(this, &AToolboxBoss::OnMyBossBeginOverlap);

	// FSM ������Ʈ �߰�
	fsm = CreateDefaultSubobject<UToolBoxBossFSM>(TEXT("FSM"));
	

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

void AToolboxBoss::OnMyBossBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �÷��̾�� �浹���� �� �÷��̾� �ı�
	//OtherActor->Destroy();
	
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Blue, TEXT("Destroy Player"));
	
}

