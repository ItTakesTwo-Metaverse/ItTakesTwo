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
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, 450),FRotator(0,-90,0));
	GetMesh()->SetRelativeScale3D(FVector(5, 5, 5));
	GetMesh()->SetCollisionProfileName(TEXT("Boss"));


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BossMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/Meshes/SKM_boss_bone_v002_body_001.SKM_boss_bone_v002_body_001'"));
	if (BossMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BossMeshAsset.Object);
	}

	// 보스 오른팔1
	RightArmMesh1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightArmMesh1"));
	RightArmMesh1->SetupAttachment(GetMesh(), TEXT("RightArmSocket"));
	RightArmMesh1->SetRelativeLocationAndRotation(FVector(-70,-90,-20),FRotator(90,0,0));
	//RightArmMesh->SetGenerateOverlapEvents(true);
	//RightArmMesh->SetCollisionProfileName(TEXT("Boss"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RightArmMesh1Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/Meshes/SKM_boss_bone_v002_Sphere_001.SKM_boss_bone_v002_Sphere_001'"));
	if (RightArmMesh1Asset.Succeeded())
	{
		RightArmMesh1->SetSkeletalMesh(RightArmMesh1Asset.Object);
	}

	// 보스 오른팔2
	RightArmMesh2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightArmMesh2"));
	RightArmMesh2->SetupAttachment(RightArmMesh1, TEXT("RightArmSocket"));
	RightArmMesh2->SetRelativeLocation(FVector(-105, -40, 20));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RightArmMesh2Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/Meshes/SKM_boss_bone_v002_Cube_001.SKM_boss_bone_v002_Cube_001'"));
	if (RightArmMesh2Asset.Succeeded())
	{
		RightArmMesh2->SetSkeletalMesh(RightArmMesh2Asset.Object);
	}

	// 보스 오른손
	RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));
	RightHandMesh->SetupAttachment(RightArmMesh2, TEXT("RightHandSocket"));
	RightHandMesh->SetRelativeLocationAndRotation(FVector(100,-70,10),FRotator(0,0,-3));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RightHandMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/Meshes/SKM_boss_bone_v002_Cube_002.SKM_boss_bone_v002_Cube_002'"));
	if (RightHandMeshAsset.Succeeded())
	{
		RightHandMesh->SetSkeletalMesh(RightHandMeshAsset.Object);
	}

	// 충돌체
	//RightArmMesh->OnComponentBeginOverlap.AddDynamic(this, &AToolboxBoss::OnMyBossBeginOverlap);

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
	
	//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Blue, TEXT("Destroy Player"));
	
}

