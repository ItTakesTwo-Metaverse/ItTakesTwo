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
#include "HSW_Hammer.h"
#include "HSW_Bullet.h"



// Sets default values
AToolboxBoss::AToolboxBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 보스 몸체
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BossMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/Meshes/SKM_boss_body.SKM_boss_body'"));
	if (BossMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BossMeshAsset.Object);
		GetMesh ( )->SetupAttachment ( RootComponent );
		GetMesh ( )->SetRelativeLocation ( FVector ( 0 , 0 , 1000 ));
		
	}

	// 보스 왼팔
	LeftArmMesh = CreateDefaultSubobject<USkeletalMeshComponent> ( TEXT ( "LeftArmMesh" ) );
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LeftArmMeshAsset ( TEXT ( "/Script/Engine.SkeletalMesh'/Game/LHM_Boss/Meshes/SKM_boss_left_arm.SKM_boss_left_arm'" ) );
	if ( LeftArmMeshAsset.Succeeded ( ) )
	{
		LeftArmMesh->SetSkeletalMesh ( LeftArmMeshAsset.Object );
		LeftArmMesh->SetupAttachment ( GetMesh ( ) , TEXT ( "LeftArmSocket" ) );
		LeftArmMesh->SetRelativeLocationAndRotation ( FVector ( 210 , -850 , 0 ) , FRotator ( 0 , -90 , 0 ) );
	}

	// 보스 오른팔
	RightArmMesh = CreateDefaultSubobject<USkeletalMeshComponent> ( TEXT ( "RightArmMesh" ) );
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RightArmMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/Meshes/newRightArm1/SKM_boss_right_arm.SKM_boss_right_arm'"));
	if (RightArmMeshAsset.Succeeded())
	{
		RightArmMesh->SetSkeletalMesh(RightArmMeshAsset.Object);
		RightArmMesh->SetupAttachment ( GetMesh ( ) , TEXT ( "RightArmSocket" ) );
		RightArmMesh->SetRelativeLocationAndRotation ( FVector ( 250 , 750 , 0 ) , FRotator ( 0 , 80 , 0 ));
		RightArmMesh->SetGenerateOverlapEvents ( true );
		RightArmMesh->SetCollisionProfileName ( TEXT ( "Boss" ) );
	}

	// 못 상호작용 박스1
	NailInteractionBox1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NailInterationBox1" ));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NailInteractionBox1Asset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'" ) );
	if ( NailInteractionBox1Asset.Succeeded ( ) )
	{
		NailInteractionBox1->SetStaticMesh( NailInteractionBox1Asset.Object);
		NailInteractionBox1->SetupAttachment(RightArmMesh, TEXT("joint7" ) );
		NailInteractionBox1->SetRelativeLocation(FVector(-720,-10,0));
		NailInteractionBox1->SetRelativeScale3D(FVector(1.5,0.3,1.5));
		NailInteractionBox1->SetGenerateOverlapEvents ( true );
		NailInteractionBox1->SetCollisionProfileName ( TEXT ( "BossNailInteractionBox" ) );
	}

	// 못 상호작용 박스2
	NailInteractionBox2 = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "NailInterationBox2" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NailInteractionBox2Asset ( TEXT ( "/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'" ) );
	if ( NailInteractionBox2Asset.Succeeded ( ) )
	{
		NailInteractionBox2->SetStaticMesh ( NailInteractionBox2Asset.Object );
		NailInteractionBox2->SetupAttachment ( RightArmMesh , TEXT ( "joint5" ) );
		NailInteractionBox2->SetRelativeLocationAndRotation ( FVector ( 235 , 0 , 15 ), FRotator(-13,0,90) );
		NailInteractionBox2->SetRelativeScale3D ( FVector ( 2 , 0.3 , 2 ) );
	}

	// 못 상호작용 박스3
	NailInteractionBox3 = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "NailInterationBox3" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NailInteractionBox3Asset ( TEXT ( "/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'" ) );
	if ( NailInteractionBox3Asset.Succeeded ( ) )
	{
		NailInteractionBox3->SetStaticMesh ( NailInteractionBox3Asset.Object );
		NailInteractionBox3->SetupAttachment ( RightArmMesh , TEXT ( "joint4" ) );
		NailInteractionBox3->SetRelativeLocationAndRotation ( FVector ( 0 , -3 ,35 ) , FRotator ( 0 , -8 , 90 ) );
		NailInteractionBox3->SetRelativeScale3D ( FVector ( 2 , 0.3 , 2 ) );
	}

	// 자물쇠1
	Lock1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lock1") );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Lock1Asset (TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'" ) );
	if ( Lock1Asset.Succeeded ( ) )
	{
		Lock1->SetStaticMesh(Lock1Asset.Object);
		Lock1->SetupAttachment(GetMesh());
		Lock1->SetRelativeLocation(FVector(-300,560,-370));
		Lock1->SetGenerateOverlapEvents ( true );
		Lock1->SetCollisionProfileName ( TEXT ( "Lock" ) );
	}

	// 자물쇠2
	Lock2 = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "Lock2" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Lock2Asset ( TEXT ( "/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'" ) );
	if ( Lock2Asset.Succeeded ( ) )
	{
		Lock2->SetStaticMesh ( Lock2Asset.Object );
		Lock2->SetupAttachment ( GetMesh ( ) );
		Lock2->SetRelativeLocation ( FVector ( -430 , 560 , -370 ) );
	}

	// 오른팔 충돌
	RightArmMesh->OnComponentBeginOverlap.AddDynamic(this, &AToolboxBoss::OnMyBossBeginOverlap);
	// 못 상호작용 박스 충돌
	NailInteractionBox1->OnComponentBeginOverlap.AddDynamic ( this , &AToolboxBoss::OnMyNailInteractionBoxBeginOverlap );
	// 자물쇠 충돌
	Lock1->OnComponentBeginOverlap.AddDynamic ( this , &AToolboxBoss::OnMyLockBeginOverlap );
	

	//// 오른팔 애니메이션 블루프린트 할당
	//ConstructorHelpers::FClassFinder<UAnimInstance> RightArmAttackClass(TEXT("/Script/Engine.AnimBlueprint'/Game/LHM_Boss/Animation/ABP_RightArm.ABP_RightArm_C'"));
	//if ( RightArmAttackClass.Succeeded ( ) )
	//{
	//	RightArmMesh->SetAnimInstanceClass(RightArmAttackClass.Class);
	//}

	// FSM 컴포넌트 추가
	fsm = CreateDefaultSubobject<UToolBoxBossFSM> ( TEXT ( "FSM" ) );
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
	if ( OtherActor->IsA<ACharacter>() )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 5.f , FColor::Blue , TEXT ( "Destroy Player" ) );
		UE_LOG ( LogTemp , Warning , TEXT ( "Destroy Player" ) );
		//OtherActor->Destroy();
		
	}
}

void AToolboxBoss::OnMyNailInteractionBoxBeginOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	// 플레이어의 못이 보스의 오른팔 상호작용 박스에 충돌했을 때 보스 일시정지 상태로 전이

	if ( OtherActor)
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 5.f , FColor::Blue , TEXT ( "Bullet Collision NailInteractionBox" ) );
		UE_LOG ( LogTemp , Warning , TEXT ( "Bullet Collision NailInteractionBox" ) );

		if ( fsm->CurrentState == EBossState::Attack1 )
		{
			GEngine->AddOnScreenDebugMessage ( -1 , 5.f , FColor::Blue , TEXT ( "Attck1 >> Paused" ) );
			UE_LOG ( LogTemp , Warning , TEXT ( "Attck1 >> Paused" ) );
			fsm->ChangeState ( EBossState::Paused );
		}
	}



	/*if ( OtherActor->ActorHasTag ( "Bullet" ) )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 5.f , FColor::Blue , TEXT ( "Bullet Has Tag NailInteractionBox" ) );
		UE_LOG ( LogTemp , Warning , TEXT ( "Bullet Has Tag NailInteractionBox" ) );

		if ( fsm->CurrentState == EBossState::Attack1 )
		{
			GEngine->AddOnScreenDebugMessage ( -1 , 5.f , FColor::Blue , TEXT ( "Attck1 >> Paused" ) );
			UE_LOG ( LogTemp , Warning , TEXT ( "Attck1 >> Paused" ) );
			fsm->ChangeState(EBossState::Paused);
		}
	}*/
}

void AToolboxBoss::OnMyLockBeginOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	// 플레이어의 망치와 충돌했을 때 자물쇠 데미지
	if ( OtherActor->IsA<AHSW_Hammer> ( ) )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 5.f , FColor::Blue , TEXT ( "Collision Hammer&Lock" ) );
		UE_LOG ( LogTemp , Warning , TEXT ( "Collision Hammer&Lock" ) );
		fsm->OnMyTakeDamage();
	}
	
}


void AToolboxBoss::EnterRagdollState ( )
{	
	/*USkeletalMeshComponent* BodyComp = GetMesh ( );
	USkeletalMeshComponent* LeftArmComp = LeftArmMesh;
	USkeletalMeshComponent* RightArmComp = RightArmMesh;*/
	//if ( BodyComp && LeftArmComp && RightArmComp )
	//{
		GetMesh ( )->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
		GetMesh ( )->SetSimulatePhysics(true);
		GetMesh ( )->WakeAllRigidBodies ( );
		GetMesh ( )->bBlendPhysics = true;
		

		LeftArmMesh->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
		LeftArmMesh->SetSimulatePhysics ( true );
		LeftArmMesh->WakeAllRigidBodies ( );
		LeftArmMesh->bBlendPhysics = true;

		RightArmMesh->SetSimulatePhysics ( true );
		RightArmMesh->WakeAllRigidBodies ( );
		RightArmMesh->bBlendPhysics = true;
		

	//}
}

void AToolboxBoss::SetAnimState ( ERightAnimState NewState )
{	
	RightArmAnimInstance = Cast<URightArmAnim> ( RightArmMesh->GetAnimInstance ( ) );
	if ( RightArmAnimInstance )
	{
		RightArmAnimInstance->SetAnimState(NewState);
	}
}

