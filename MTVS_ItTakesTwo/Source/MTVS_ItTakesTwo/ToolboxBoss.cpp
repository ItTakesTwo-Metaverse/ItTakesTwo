// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolboxBoss.h"
#include "Components/SkeletalMeshComponent.h"
#include "ToolBoxBossFSM.h"
#include "Components/SceneComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "RightArmAnim.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
AToolboxBoss::AToolboxBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 보스 몸체
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BossMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/newBoss/SKM_boss_body.SKM_boss_body'"));
	if (BossMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BossMeshAsset.Object);
		GetMesh ( )->SetupAttachment ( RootComponent );
		GetMesh ( )->SetRelativeLocation ( FVector ( 0 , 0 , 1000 ));
		GetMesh ( )->SetCollisionProfileName ( TEXT ( "Boss" ) );
	}

	// 보스 왼팔
	LeftArmMesh = CreateDefaultSubobject<USkeletalMeshComponent> ( TEXT ( "LeftArmMesh" ) );

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LeftArmMeshAsset ( TEXT ( "/Script/Engine.SkeletalMesh'/Game/LHM_Boss/newBoss/SKM_boss_left_arm.SKM_boss_left_arm'" ) );
	if ( LeftArmMeshAsset.Succeeded ( ) )
	{
		LeftArmMesh->SetSkeletalMesh ( LeftArmMeshAsset.Object );
		LeftArmMesh->SetupAttachment ( GetMesh ( ) , TEXT ( "LeftArmSocket" ) );
		LeftArmMesh->SetRelativeLocationAndRotation ( FVector ( 210 , -850 , 0 ) , FRotator ( 0 , -90 , 0 ) );
	}

	// 보스 오른팔
	RightArmMesh = CreateDefaultSubobject<USkeletalMeshComponent> ( TEXT ( "RightArmMesh" ) );

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RightArmMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/newBoss/SKM_boss_right_arm.SKM_boss_right_arm'"));
	if (RightArmMeshAsset.Succeeded())
	{
		RightArmMesh->SetSkeletalMesh(RightArmMeshAsset.Object);
		RightArmMesh->SetupAttachment ( GetMesh ( ) , TEXT ( "RightArmSocket" ) );
		RightArmMesh->SetRelativeLocationAndRotation ( FVector ( 250 , 750 , 0 ) , FRotator ( 0 , 80 , 0 ));
		RightArmMesh->SetGenerateOverlapEvents ( true );
		RightArmMesh->SetCollisionProfileName ( TEXT ( "Boss" ) );
	}

	// 못 상호작용 박스 3개
	NailInterationBox1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NailInterationBox1" ));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> NailInterationBox1Asset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'" ) );
	if ( NailInterationBox1Asset.Succeeded ( ) )
	{
		NailInterationBox1->SetStaticMesh( NailInterationBox1Asset .Object);
		NailInterationBox1->SetupAttachment(RightArmMesh, TEXT("joint7" ) );
		NailInterationBox1->SetRelativeLocation(FVector(-650,0,0));
		NailInterationBox1->SetRelativeScale3D(FVector(1,0.3,1));
	}

	NailInterationBox2 = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "NailInterationBox2" ) );

	static ConstructorHelpers::FObjectFinder<UStaticMesh> NailInterationBox2Asset ( TEXT ( "/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'" ) );
	if ( NailInterationBox2Asset.Succeeded ( ) )
	{
		NailInterationBox2->SetStaticMesh ( NailInterationBox2Asset.Object );
		NailInterationBox2->SetupAttachment ( RightArmMesh , TEXT ( "joint5" ) );
		NailInterationBox2->SetRelativeLocationAndRotation ( FVector ( 240 , -30 , 0 ), FRotator(-3,0,0) );
		NailInterationBox2->SetRelativeScale3D ( FVector ( 2 , 0.3 , 2 ) );

	}

	NailInterationBox3 = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "NailInterationBox3" ) );

	static ConstructorHelpers::FObjectFinder<UStaticMesh> NailInterationBox3Asset ( TEXT ( "/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'" ) );
	if ( NailInterationBox3Asset.Succeeded ( ) )
	{
		NailInterationBox3->SetStaticMesh ( NailInterationBox3Asset.Object );
		NailInterationBox3->SetupAttachment ( RightArmMesh , TEXT ( "joint4" ) );
		NailInterationBox3->SetRelativeLocationAndRotation ( FVector ( 0 , -30 ,0 ) , FRotator ( 0 , -8 , 0 ) );
		NailInterationBox3->SetRelativeScale3D ( FVector ( 2 , 0.3 , 2 ) );

	}

	// 태그 설정하기~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RightArmMesh->ComponentHasTag ( TEXT ( "testtag") );

	// 충돌체
	RightArmMesh->OnComponentBeginOverlap.AddDynamic(this, &AToolboxBoss::OnMyBossBeginOverlap);
	

	// FSM 컴포넌트 추가
	fsm = CreateDefaultSubobject<UToolBoxBossFSM>(TEXT("FSM"));
	

	// 오른팔 애니메이션 블루프린트 할당
	ConstructorHelpers::FClassFinder<UAnimInstance> RightArmAttackClass(TEXT("/Script/Engine.AnimBlueprint'/Game/LHM_Boss/Animation/ABP_RightArm.ABP_RightArm_C'"));
	if ( RightArmAttackClass.Succeeded ( ) )
	{
		RightArmMesh->SetAnimInstanceClass(RightArmAttackClass.Class);
	}
	
}

// Called when the game starts or when spawned
void AToolboxBoss::BeginPlay()
{
	Super::BeginPlay();
	
	

	RightArmAnimInstance = Cast<URightArmAnim>(RightArmMesh->GetAnimInstance());

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
	if ( OtherActor->IsA<ACharacter>() )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 5.f , FColor::Blue , TEXT ( "Destroy Player" ) );
		//OtherActor->Destroy();
	}
}



void AToolboxBoss::SetAnimState ( ERightAnimState NewState )
{
	if ( RightArmAnimInstance )
	{
		RightArmAnimInstance->SetAnimState(NewState);
	}
}

