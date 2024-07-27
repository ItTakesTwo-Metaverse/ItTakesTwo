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
	
	// 보스 몸체
	
	GetMesh()->SetupAttachment(RootComponent);
	GetMesh()->SetRelativeLocation(FVector(0, 0, 450));
	GetMesh()->SetRelativeScale3D(FVector(5, 10, 10));
	GetMesh()->SetCollisionProfileName(TEXT("Boss"));


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BossMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'"));
	if (BossMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BossMeshAsset.Object);
	}

	// 보스 왼팔
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

	// 보스 오른팔
	RightArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightArmMesh"));
	RightArmMesh->SetupAttachment(GetMesh(), TEXT("RightArmSocket"));
	RightArmMesh->SetRelativeLocation(FVector(0, 12, 20));
	RightArmMesh->SetRelativeRotation(FRotator(-10, 270, -90));
	RightArmMesh->SetRelativeScale3D(FVector(0.05, 0.3, 0.05));
	RightArmMesh->SetCollisionProfileName(TEXT("Boss"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RightArmMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
	if (RightArmMeshAsset.Succeeded())
	{
		RightArmMesh->SetSkeletalMesh(RightArmMeshAsset.Object);
	}

	// 보스 오른손
	RightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHandMesh"));
	RightHandMesh->SetupAttachment(RightArmMesh, TEXT("RightHandSocket"));
	RightHandMesh->SetRelativeLocation(FVector(0, 0, -260));
	RightHandMesh->SetRelativeRotation(FRotator(0, 0, -90));
	RightHandMesh->SetGenerateOverlapEvents(true);
	RightHandMesh->SetCollisionProfileName(TEXT("Boss"));

	// 충돌체
	RightHandMesh->OnComponentBeginOverlap.AddDynamic(this, &AToolboxBoss::OnMyBossBeginOverlap);

	// FSM 컴포넌트 추가
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
	// 플레이어와 충돌했을 때 플레이어 파괴
	//OtherActor->Destroy();
}

