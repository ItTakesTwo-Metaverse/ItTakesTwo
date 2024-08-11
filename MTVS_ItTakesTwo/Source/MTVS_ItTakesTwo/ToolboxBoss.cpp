// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolboxBoss.h"
#include "Components/SkeletalMeshComponent.h"
#include "ToolBoxBossFSM.h"
#include "Components/SceneComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "HSW_Hammer.h"
#include "HSW_Bullet.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "CSR_Player_May.h"
#include "CSR_Player_Cody.h"



// Sets default values
AToolboxBoss::AToolboxBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 보스 몸체
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BossMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/BossMeshes/SKM_boss_fin_body.SKM_boss_fin_body'"));
	if (BossMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BossMeshAsset.Object);
		GetMesh ( )->SetupAttachment ( RootComponent );
		
	}

	// 보스 왼팔
	LeftArmMesh = CreateDefaultSubobject<USkeletalMeshComponent> ( TEXT ( "LeftArmMesh" ) );
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LeftArmMeshAsset ( TEXT ( "/Script/Engine.SkeletalMesh'/Game/LHM_Boss/BossMeshes/SKM_boss_fin_left_arm.SKM_boss_fin_left_arm'" ) );
	if ( LeftArmMeshAsset.Succeeded ( ) )
	{
		LeftArmMesh->SetSkeletalMesh ( LeftArmMeshAsset.Object );
		LeftArmMesh->SetupAttachment ( GetMesh ( ) , TEXT ( "LeftArmSocket" ) );
		LeftArmMesh->SetRelativeLocationAndRotation ( FVector ( 210 , -850 , 0 ) , FRotator ( 0 , -90 , 0 ) );
	}

	// 보스 오른팔
	RightArmMesh = CreateDefaultSubobject<USkeletalMeshComponent> ( TEXT ( "RightArmMesh" ) );
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RightArmMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/BossMeshes/SKM_boss_fin_right_arm.SKM_boss_fin_right_arm'"));
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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NailInteractionBox1Asset(TEXT("/Script/Engine.StaticMesh'/Game/LHM_Boss/BossMeshes/target/Target1.Target1'" ) );
	if ( NailInteractionBox1Asset.Succeeded ( ) )
	{
		NailInteractionBox1->SetStaticMesh( NailInteractionBox1Asset.Object);
		NailInteractionBox1->SetupAttachment(RightArmMesh, TEXT("joint20" ) );
		NailInteractionBox1->SetRelativeLocation(FVector( -2546 , -523 , 386 )); 
		NailInteractionBox1->SetGenerateOverlapEvents ( true );
		NailInteractionBox1->SetCollisionProfileName ( TEXT ( "BossNailInteractionBox" ) );
	}

	// 못 상호작용 박스2
	NailInteractionBox2 = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "NailInterationBox2" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NailInteractionBox2Asset ( TEXT ( "/Script/Engine.StaticMesh'/Game/LHM_Boss/BossMeshes/target/target2.target2'" ) );
	if ( NailInteractionBox2Asset.Succeeded ( ) )
	{
		NailInteractionBox2->SetStaticMesh ( NailInteractionBox2Asset.Object );
		NailInteractionBox2->SetupAttachment ( RightArmMesh , TEXT ( "joint5" ) );
		NailInteractionBox2->SetRelativeLocationAndRotation ( FVector ( -1145 , -42 , -520 ), FRotator( -1 , 0 , -124 ) );
		NailInteractionBox1->SetGenerateOverlapEvents ( true );
		NailInteractionBox1->SetCollisionProfileName ( TEXT ( "BossNailInteractionBox" ) );
	}

	// 못 상호작용 박스3
	NailInteractionBox3 = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "NailInterationBox3" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> NailInteractionBox3Asset ( TEXT ( "/Script/Engine.StaticMesh'/Game/LHM_Boss/BossMeshes/target/Target3.Target3'" ) );
	if ( NailInteractionBox3Asset.Succeeded ( ) )
	{
		NailInteractionBox3->SetStaticMesh ( NailInteractionBox3Asset.Object );
		NailInteractionBox3->SetupAttachment ( RightArmMesh , TEXT ( "joint4" ) ); 
		NailInteractionBox3->SetRelativeLocationAndRotation ( FVector ( -1033 , 54 , -254 ) , FRotator ( -12 , -10 , -107 ) );
		NailInteractionBox1->SetGenerateOverlapEvents ( true );
		NailInteractionBox1->SetCollisionProfileName ( TEXT ( "BossNailInteractionBox" ) );
	}

	// 자물쇠1
	Lock1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Lock1") );
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Lock1Asset (TEXT("/Script/Engine.SkeletalMesh'/Game/LHM_Boss/BossMeshes/lock/SM_Locker_002.SM_Locker_002'" ) );
	if ( Lock1Asset.Succeeded ( ) )
	{
		Lock1->SetSkeletalMesh (Lock1Asset.Object);
		Lock1->SetupAttachment(GetMesh());
		Lock1->SetRelativeLocation(FVector( -318 , 553 , -397 ));
	}

	LockBody1 = CreateDefaultSubobject<USkeletalMeshComponent> ( TEXT ( "LockBody1" ) );
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LockBody1Asset ( TEXT ( "/Script/Engine.SkeletalMesh'/Game/LHM_Boss/BossMeshes/lock/SM_Locker_001.SM_Locker_001'" ) );
	if ( LockBody1Asset.Succeeded ( ) )
	{
		LockBody1->SetSkeletalMesh ( LockBody1Asset.Object );
		LockBody1->SetupAttachment ( Lock1 );
		LockBody1->SetGenerateOverlapEvents ( true );
		LockBody1->SetCollisionProfileName ( TEXT ( "Lock" ) );
	}

	// 자물쇠2
	Lock2 = CreateDefaultSubobject<USkeletalMeshComponent> ( TEXT ( "Lock2" ) );
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Lock2Asset ( TEXT ( "/Script/Engine.SkeletalMesh'/Game/LHM_Boss/BossMeshes/lock/SM_Locker_002.SM_Locker_002'" ) );
	if ( Lock2Asset.Succeeded ( ) )
	{
		Lock2->SetSkeletalMesh ( Lock2Asset.Object );
		Lock2->SetupAttachment ( GetMesh ( ) );
		Lock2->SetRelativeLocation ( FVector ( -388 , 553 , -397 ) );
	}

	LockBody2 = CreateDefaultSubobject<USkeletalMeshComponent> ( TEXT ( "LockBody2" ) );
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LockBody2Asset ( TEXT ( "/Script/Engine.SkeletalMesh'/Game/LHM_Boss/BossMeshes/lock/SM_Locker_001.SM_Locker_001'" ) );
	if ( LockBody2Asset.Succeeded ( ) )
	{
		LockBody2->SetSkeletalMesh ( LockBody2Asset.Object );
		LockBody2->SetupAttachment ( Lock2 );
		LockBody2->SetGenerateOverlapEvents ( true );
		LockBody2->SetCollisionProfileName ( TEXT ( "Lock" ) );
	}

	// 전동 드릴
	Drill = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Drill" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DrillAsset ( TEXT ( "//Script/Engine.StaticMesh'/Game/LHM_Boss/BossMeshes/drill/drill_DRILL.drill_DRILL'" ) );
	if( DrillAsset .Succeeded())
	{
		Drill->SetStaticMesh ( DrillAsset.Object );
		Drill->SetupAttachment( RightArmMesh , TEXT ( "joint8" ) );
		Drill->SetRelativeLocationAndRotation ( FVector ( 290 , -520 , 480 ), FRotator(6,0,0 ));
		Drill->SetGenerateOverlapEvents ( true );
		Drill->SetCollisionProfileName ( TEXT ( "Drill" ) );
		Drill->SetVisibility ( false );
	}

	DrillCircle = CreateDefaultSubobject<USkeletalMeshComponent> ( TEXT ( "DrillCircle" ) );
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DrillCircleAsset ( TEXT ( "/Script/Engine.SkeletalMesh'/Game/LHM_Boss/BossMeshes/drill/SKM_drill_circle.SKM_drill_circle'" ) );
	if ( DrillCircleAsset.Succeeded ( ) )
	{
		DrillCircle->SetSkeletalMesh ( DrillCircleAsset.Object );
		DrillCircle->SetupAttachment ( Drill ); 
		DrillCircle->SetRelativeLocationAndRotation ( FVector ( -5 , 448 , -60 ), FRotator( 0, 0, 84 ) );
		DrillCircle->SetGenerateOverlapEvents ( true );
		DrillCircle->SetCollisionProfileName ( TEXT ( "Drill" ) );
		DrillCircle->SetVisibility ( false );
	}

	DrillArms = CreateDefaultSubobject<USkeletalMeshComponent> ( TEXT ( "DrillArms" ) );
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DrillArmsAsset ( TEXT ( "/Script/Engine.SkeletalMesh'/Game/LHM_Boss/BossMeshes/drill/SKM_DrillArms.SKM_DrillArms'" ) );
	if ( DrillArmsAsset.Succeeded ( ) )
	{
		DrillArms->SetSkeletalMesh ( DrillArmsAsset.Object );
		DrillArms->SetupAttachment ( DrillCircle ); 
		DrillArms->SetRelativeLocationAndRotation ( FVector ( 0 , -2.5 , -2 ) , FRotator ( -82 , -90 , 90 ) );
		DrillArms->SetGenerateOverlapEvents ( true );
		DrillArms->SetCollisionProfileName ( TEXT ( "Drill" ) );
		DrillArms->SetVisibility ( false );
	}

	
	// 오른팔 충돌
	RightArmMesh->OnComponentBeginOverlap.AddDynamic(this, &AToolboxBoss::OnMyBossBeginOverlap);
	// 못 상호작용 박스 충돌
	NailInteractionBox1->OnComponentBeginOverlap.AddDynamic ( this , &AToolboxBoss::OnMyNailInteractionBoxBeginOverlap );
	// 자물쇠 충돌
	LockBody1->OnComponentBeginOverlap.AddDynamic ( this , &AToolboxBoss::OnMyLockBeginOverlap );
	LockBody2->OnComponentBeginOverlap.AddDynamic ( this , &AToolboxBoss::OnMyLockBeginOverlap );
	// 드릴 충돌
	DrillCircle->OnComponentBeginOverlap.AddDynamic ( this , &AToolboxBoss::OnMyDrillCirleOverlap );
	DrillArms->OnComponentBeginOverlap.AddDynamic ( this , &AToolboxBoss::OnMyDrillOverlap );

	// 오른팔 애니메이션 블루프린트 할당
	ConstructorHelpers::FClassFinder<UAnimInstance> TempRightArmAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/LHM_Boss/Anim/ABP_RightArm.ABP_RightArm'_C'"));
	if ( TempRightArmAnim.Succeeded ( ) )
	{
		RightArmMesh->SetAnimInstanceClass( TempRightArmAnim.Class);
	}

	DrillCircleAnim = Cast<UDrillCircleAnimInstance> ( DrillCircle->GetAnimInstance ( ) );

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
	// 플레이어와 충돌했을 때 플레이어 죽음
	if ( OtherActor->IsA<ACSR_Player_May>() || OtherActor->IsA<ACSR_Player_Cody>() )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 5.f , FColor::Blue , TEXT ( "Destroy Player" ) );
		UE_LOG ( LogTemp , Warning , TEXT ( "Destroy Player" ) );
		//OtherActor->Destroy();
	}
	
}

void AToolboxBoss::OnMyNailInteractionBoxBeginOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	// 플레이어의 못이 보스의 오른팔 상호작용 박스에 충돌했을 때 보스 일시정지 상태로 전이
	if ( OtherActor )
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
}

void AToolboxBoss::OnMyLockBeginOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	GEngine->AddOnScreenDebugMessage ( -1 , 5.f , FColor::Blue , TEXT ( "Collision Lock & Hammer" ) );
	UE_LOG ( LogTemp , Warning , TEXT ( "Collision Lock & Hammer" ) );

	// 플레이어의 망치와 충돌했을 때 자물쇠 데미지
	if ( OtherActor )
	{
		if ( Lock1HP > 0 )
		{
			Lock1HP -= damage;
			if ( Lock1HP == 0 )
			{
				Lock1->DestroyComponent ( );
				LockBody1->DestroyComponent ( );

				//LockBody2->SetCollisionEnabled() // 자물쇠 1개가 파괴되는 순간에만 LockBody2를 Block 처리 하고싶다.
			}
		}
		else if ( Lock1HP == 0 && Lock2HP > 0)
		{
			Lock2HP -= damage;
			if ( Lock2HP == 0 )
			{
				Lock2->DestroyComponent ( );
				LockBody2->DestroyComponent ( );
			}
		}
	}

}

void AToolboxBoss::OnMyDrillCirleOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComponent , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{	
	// 드릴공격 판자 뚫기
	if ( OtherActor && OtherActor != this )
	{
		if ( OtherComponent && OtherComponent->ComponentHasTag ( TEXT ( "HoleMesh" ) ) )
		{
			OtherActor->Destroy ( );
		}
	}
}

void AToolboxBoss::OnMyDrillOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComponent , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	// 플레이어와 충돌했을 때 플레이어 죽음
	if ( OtherActor->IsA<ACharacter> ( ) )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 5.f , FColor::Blue , TEXT ( "Destroy Player" ) );
		UE_LOG ( LogTemp , Warning , TEXT ( "Destroy Player" ) );
		//OtherActor->Destroy();
	}
}

void AToolboxBoss::EnterRagdollState ( )
{	
	if ( RightArmMesh )
	{
		RightArmMesh->SetSimulatePhysics ( true );
		//RightArmMesh->WakeAllRigidBodies ( );
		//RightArmMesh->bBlendPhysics = true;
	}
	if ( GetMesh ( ) )
	{
		GetMesh()->SetSimulatePhysics(true);
	}
	if ( LeftArmMesh )
	{
		LeftArmMesh->SetSimulatePhysics ( true );
	}
}

void AToolboxBoss::SetAnimState ( ERightArmAnimState NewState )
{	
	RightArmAnimInstance = Cast<URightArmAnimInstance> ( RightArmMesh->GetAnimInstance ( ) );
	if ( RightArmAnimInstance )
	{
		RightArmAnimInstance->SetAnimState(NewState);
	}
}

