// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HSW_BulletManager.h"

// Sets default values
AHSW_Bullet::AHSW_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//충돌체
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetCollisionProfileName(TEXT("Bullet"));
	BoxComp->SetEnableGravity ( false );
	BoxComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );

	//외형
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//발사체
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent> ( TEXT ( "MovementComp" ) );
	MovementComp->SetUpdatedComponent ( RootComponent );
	MovementComp->bShouldBounce = false;
	MovementComp->ProjectileGravityScale = 0;

	//유도탄 설정
	MovementComp->bIsHomingProjectile = false;
	MovementComp->HomingAccelerationMagnitude = 3000;


	//해머 인터렉션 Overlap
	NailHammerComp = CreateDefaultSubobject<UBoxComponent> ( TEXT ( "NailHammerComp" ) );
	NailHammerComp->SetupAttachment ( RootComponent );
	NailHammerComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
	NailHammerComp->SetBoxExtent ( FVector ( 50.f ) );


}

// Called when the game starts or when spawned
void AHSW_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentHit.AddDynamic( this , &AHSW_Bullet::OnMyWallHit );

	Player = GetWorld ( )->GetFirstPlayerController ( )->GetPawn ( );
	//GetWorld ( )->GetTimerManager ( ).SetTimer ( TimerHandle , this , &AHSW_Bullet::LoadSecondPlayer , 0.2f , false );

	//StartPoint = Player->GetActorLocation ( );
	//EndPoint = StartPoint + FVector ( 100000 , 0 , 0 );

	
	//NailHomingTargetComponent = player->GetComponentByClass<USceneComponent> ( );
}

// Called every frame
void AHSW_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FString myState = UEnum::GetValueAsString ( State );
	DrawDebugString ( GetWorld ( ) , this->GetActorLocation ( ) , myState , nullptr , FColor::Yellow , 0 , true , 1 );
	switch ( State )
	{
	case ENailState::BASIC:			TickBasic ( DeltaTime );			break;
	case ENailState::LOAD:			TickLoad ( DeltaTime );			break;
	case ENailState::SHOOT:			TickShoot ( DeltaTime );			break;
	case ENailState::EMBEDDED:		TickEmbedded ( DeltaTime );			break;
	case ENailState::UNEMBEDDED:	TickUnembedded ( DeltaTime );		break;
	case ENailState::RETURNING:		TickReturning ( DeltaTime );		break;
	case ENailState::GOTOBAG:		TickGoToBag ( DeltaTime );		break;
	}
}

void AHSW_Bullet::OnMyWallHit ( UPrimitiveComponent* HitComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit )
{

	if ( OtherComp->ComponentHasTag ( TEXT ( "NailTag" ) ) )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "CollisionHit" ) );
		SetState(ENailState::EMBEDDED);
	}
	else if ( OtherActor->ActorHasTag ( TEXT ( "Wall1" ) ) )
	{
	//	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Red , TEXT ( "Wall1" ) );
		SetState ( ENailState::EMBEDDED );
	}
	//else if ( OtherActor->ActorHasTag ( TEXT ( "Wall2" ) ) )
	//{
	//	State = ENailState::UNEMBEDDED;
	//}
	else
	{
		SetState(ENailState::UNEMBEDDED);
	}
}


void AHSW_Bullet::TickBasic ( const float& DeltaTime )
{
	//MovementComp->bIsHomingProjectile = false;
	// 
	// TO DO
	// 

	// 조건
	// 못이 벽에 박혔다면
	// -> Embedded 상태로 변경.
	// 못이 벽에 박히지 못했다면
	// -> Unembedded 상태로 변경.
	//SetState ( ENailState::SHOOT );
}

void AHSW_Bullet::TickLoad ( const float& DeltaTime )
{
	//
}

void AHSW_Bullet::TickShoot ( const float& DeltaTime )
{

	/*	auto* player = GetWorld ( )->GetFirstPlayerController ( )->GetPawn();
	USkeletalMeshComponent* MeshComponent = Cast<USkeletalMeshComponent> ( player->GetComponentByClass ( USkeletalMeshComponent::StaticClass ( ) ) );
	FTransform PlayerSocketTransform = MeshComponent->GetSocketTransform ( TEXT ( "!!소켓이름!!" ))
*/
	//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "SHOOOOOOOT" ) );

	FVector dir =  EndPoint - StartPoint ;
	dir.Normalize ( );
	SetActorLocation (GetActorLocation() + dir* Speed * DeltaTime, true);
}

void AHSW_Bullet::TickEmbedded ( const float& DeltaTime )
{
	// To Do
	// 벽에 박힌 채 가만히 있고싶다.
	// 망치와 상호작용하고싶다.

	// 조건
	// 플레이어가 E키를 누르면
	// -> Returning 상태로 변경
}

void AHSW_Bullet::TickUnembedded ( const float& DeltaTime )
{

	// To Do
	// 벽에서 튕겨나가고 싶다.
	// 3초 후가 되거나 E키가 눌러지면 플레이어에게 되돌아가고 싶다.

	// 조건
	// 플레이어에게 돌아가면
	// -> Basic 상태로 변경.

}

void AHSW_Bullet::TickReturning ( const float& DeltaTime )
{
	// To Do
	// 플레이어에게 곡선을 그리며 이동하고싶다.

	//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Return" ) );
	//APlayerController* SecondPlayerController = UGameplayStatics::GetPlayerController ( GetWorld ( ) , 1 );
	//auto* player = SecondPlayerController->GetPawn();
	Distance = (Player->GetActorLocation() - this->GetActorLocation ( )).Size();
	SetActorLocation ( FMath::Lerp ( this->GetActorLocation ( ) , Player->GetActorLocation ( ) , 0.1 ));
	//SetNailReturnDestination ( );
	//Distance = (nailDestLocation - this->GetActorLocation()).Size ( );
	//SetActorLocationAndRotation ( FMath::Lerp ( this->GetActorLocation ( ) , nailDestLocation , 0.1 ) , FMath::Lerp ( this->GetActorRotation ( ) , nailDestRotation , 0.1 ) );
	//UE_LOG ( LogTemp , Warning , TEXT ( "%f" ),dist );

	//MovementComp->bIsHomingProjectile = true;

	// 해머 인터렉션 콜리전을 없앤다.

	//Bounce를 다시 활성화시킨다.
	

	// 조건
	// 플레이어에게 도착하면 
	if ( Distance < NailDefaultDist )
	{
	//	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "End" ) );


		GoToNailBag ( );
		// Basic상태로 변경.
		SetState(ENailState::BASIC);
	}
	
}


void AHSW_Bullet::TickGoToBag ( const float& DeltaTime )
{
	GoToNailBag ( );
}

void AHSW_Bullet::SetState ( ENailState NextState)
{

	State = NextState;
	

	switch ( State )
	{
	case ENailState::BASIC:
		MovementComp->ProjectileGravityScale = 0;	
		MovementComp->bShouldBounce = true;
		MeshComp->SetVisibility ( true );
		BoxComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
		NailHammerComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
		break;
	case ENailState::SHOOT:
		BoxComp->SetCollisionEnabled ( ECollisionEnabled::QueryAndPhysics );
		break;
	case ENailState::EMBEDDED:
		MovementComp->bShouldBounce = false;

		NailHammerComp->SetCollisionEnabled ( ECollisionEnabled::QueryOnly );
		break;
	case ENailState::UNEMBEDDED:
		BoxComp->SetEnableGravity ( true);
		MovementComp->bShouldBounce = true;
		MovementComp->ProjectileGravityScale = 1.f;

		break;
	case ENailState::RETURNING:
		BoxComp->SetEnableGravity ( false );
		BoxComp->SetCollisionEnabled ( ECollisionEnabled::QueryOnly );

		MovementComp->bShouldBounce = false;
		MovementComp->ProjectileGravityScale = 0;

		NailHammerComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
		break;
	case ENailState::GOTOBAG:

		break;
	default:
		break;
	}
}

void AHSW_Bullet::SetActive ( bool bValue )
{
	MeshComp->SetVisibility ( bValue );
	if ( bValue )
	{
		BoxComp->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
	}
	else
	{
		BoxComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
	}
}

//리턴될때 소켓 hand_l의 위치를 받는다.
void AHSW_Bullet::SetNailReturnDestination ()
{
//	nailDestLocation = NailBag->MeshComp->GetSocketLocation(TEXT("hand_l" ));
//	nailDestRotation = NailBag->MeshComp->GetSocketRotation ( TEXT ( "hand_l" ) );
}

// NailPop 되면서 손위에 올려놓을 때 쓰는 함수
void AHSW_Bullet::NailReadytoShoot ( FVector v , FRotator r )
{
	SetActorLocationAndRotation ( v , r );
}

void AHSW_Bullet::GoToNailBag ( )
{
	// Nail이 들어갈 소켓 이름을 가져온다.
	FString socketNameString = FString::Printf ( TEXT ( "NailBag_%d" ) , NailBag->Magazine.Num ( )-1 );
	FName socketName ( *socketNameString );
	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , socketNameString );

	// 해당 소켓이름에 맞는 곳에 attach 한다.
	AttachToActor ( NailBag , FAttachmentTransformRules::SnapToTargetIncludingScale , socketName );
	FTransform t = NailBag->MeshComp->GetSocketTransform ( socketName );
	SetActorLocation ( t.GetLocation ( ) );
	SetActorRotation ( t.GetRotation ( ) );
}

void AHSW_Bullet::SetNailBag ( AHSW_BulletManager* nailBag )
{
	NailBag = nailBag;
}

void AHSW_Bullet::NailBasic ( )
{
	this->DetachFromActor ( FDetachmentTransformRules::KeepRelativeTransform );
	GoToNailBag ( );
	SetState ( ENailState::BASIC );
}

// 마우스 좌클릭시 사용될 함수
void AHSW_Bullet::NailShoot ( FVector start , FVector end )
{
	//Nail이 오른손 소켓에서 detach됨. (if attach되어있다면, detach하고)
	if ( this->IsAttachedTo ( Player ) )
	{
		this->DetachFromActor ( FDetachmentTransformRules::KeepWorldTransform );
	}
	//Nail의 StartPoint와 EndPoint를 설정해줌. ( Lay의 Start와 End가 들어올 것이다.)
	StartPoint = start;
	EndPoint = end;

	//Nail이 Shoot 상태로 변경됨. (SetState 실행)
	SetState ( ENailState::SHOOT );
}

void AHSW_Bullet::NailLoad ( FName socketName )
{
	if ( IsAttachedTo ( NailBag ) )
	{
		DetachFromActor ( FDetachmentTransformRules::KeepRelativeTransform );
		AttachToActor ( Player , FAttachmentTransformRules::SnapToTargetIncludingScale , socketName );
	}



// 	USkeletalMeshComponent* Mesh = Player->FindComponentByClass<USkeletalMeshComponent> ( );
// 
// 	FTransform t = Mesh->GetSocketTransform ( socketName );
// 	SetActorLocation ( t.GetLocation ( ) );
// 	SetActorRotation ( Player->GetActorTransform().GetRotation ( ) );
	SetState ( ENailState::LOAD );

}

void AHSW_Bullet::NailReturn ( )
{
	SetState ( ENailState::RETURNING );
}

void AHSW_Bullet::LoadSecondPlayer ( )
{
	APlayerController* SecondPlayerController = UGameplayStatics::GetPlayerController ( GetWorld ( ) , 1 );
	Player = SecondPlayerController->GetPawn ( );
	if ( Player == nullptr)
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT("Player nullptr !!!!!" ));
	}
}
