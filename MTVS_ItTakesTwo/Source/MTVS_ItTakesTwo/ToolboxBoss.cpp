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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BossMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/BossCharacter/SKM_Body.SKM_Body'"));
	if (BossMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BossMeshAsset.Object);
	}

	// 보스 왼팔
	LeftArmMesh = CreateDefaultSubobject<USkeletalMeshComponent> ( TEXT ( "LeftArmMesh" ) );
	LeftArmMesh->SetupAttachment ( GetMesh ( ) , TEXT ( "LeftArmSocket" ) );
	LeftArmMesh->SetRelativeLocationAndRotation ( FVector ( 135 , 100 , -60 ), FRotator(0,-90,50));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LeftArmMeshAsset ( TEXT ( "/Script/Engine.SkeletalMesh'/Game/LHM_Boss/BossCharacter/SKM_Left.SKM_Left'" ) );
	if ( LeftArmMeshAsset.Succeeded ( ) )
	{
		LeftArmMesh->SetSkeletalMesh ( LeftArmMeshAsset.Object );
	}

	// 보스 오른팔
	RightArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightArmMesh"));
	RightArmMesh->SetupAttachment(GetMesh(), TEXT("RightArmSocket"));
	RightArmMesh->SetRelativeLocationAndRotation ( FVector ( -148 , 107 , -18 ),FRotator(0,80,0));
	RightArmMesh->SetGenerateOverlapEvents(true);
	RightArmMesh->SetCollisionProfileName(TEXT("Boss"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RightArmMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/BossCharacter/SKM_Right.SKM_Right'"));
	if (RightArmMeshAsset.Succeeded())
	{
		RightArmMesh->SetSkeletalMesh(RightArmMeshAsset.Object);
	}

	

	// 충돌체
	RightArmMesh->OnComponentBeginOverlap.AddDynamic(this, &AToolboxBoss::OnMyBossBeginOverlap);

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
	
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Blue, TEXT("Destroy Player"));
	
}

