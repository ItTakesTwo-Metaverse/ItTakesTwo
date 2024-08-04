// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

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


	auto* player = GetWorld ( )->GetFirstPlayerController ( )->GetPawn ( );
	StartPoint = player->GetActorLocation ( );
	EndPoint = StartPoint + FVector ( 0 , 0 , -100000 );


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
	case ENailState::SHOOT:			TickShoot ( DeltaTime );			break;
	case ENailState::EMBEDDED:		TickEmbedded ( DeltaTime );			break;
	case ENailState::UNEMBEDDED:	TickUnembedded ( DeltaTime );		break;
	case ENailState::RETURNING:		TickReturning ( DeltaTime );		break;
	}

}

void AHSW_Bullet::OnMyWallHit ( UPrimitiveComponent* HitComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit )
{

	if ( OtherActor->ActorHasTag ( TEXT ( "NailTag" ) ) )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Red , TEXT ( "Tag: NailTag" ) );
		SetState(ENailState::EMBEDDED);
	}
	if ( OtherActor->ActorHasTag ( TEXT ( "Wall1" ) ) )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Red , TEXT ( "Wall1" ) );
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
	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Red , TEXT ( "Basic" ) );
	//MovementComp->bIsHomingProjectile = false;
	// 
	// TO DO
	// 

	// 조건
	// 못이 벽에 박혔다면
	// -> Embedded 상태로 변경.
	// 못이 벽에 박히지 못했다면
	// -> Unembedded 상태로 변경.

	SetState ( ENailState::SHOOT );
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
	SetActorLocation (GetActorLocation() + dir* Speed * DeltaTime,true);
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

	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Return" ) );
	auto* player = GetWorld ( )->GetFirstPlayerController ( )->GetPawn ( );
	Distance = (player->GetActorLocation() - this->GetActorLocation ( )).Size();
	SetActorLocation ( FMath::Lerp ( this->GetActorLocation ( ) , player->GetActorLocation ( ) , 0.1 ));
	//UE_LOG ( LogTemp , Warning , TEXT ( "%f" ),dist );

	//MovementComp->bIsHomingProjectile = true;

	// 해머 인터렉션 콜리전을 없앤다.

	//Bounce를 다시 활성화시킨다.
	

	// 조건
	// 플레이어에게 도착하면 
	if ( Distance < NailDefaultDist )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "End" ) );
		SetState(ENailState::BASIC);
	}
	// -> Basic상태로 변경.
}


void AHSW_Bullet::SetState ( ENailState NextState )
{

	State = NextState;
	

	switch ( State )
	{
	case ENailState::BASIC:
		MovementComp->ProjectileGravityScale = 0;	
		MovementComp->bShouldBounce = true;
		break;
	case ENailState::SHOOT:
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
		MovementComp->bShouldBounce = false;
		MovementComp->ProjectileGravityScale = 0;

		NailHammerComp->SetCollisionEnabled ( ECollisionEnabled::QueryOnly );
		break;
	default:
		break;
	}
}
