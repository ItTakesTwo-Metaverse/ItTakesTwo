// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HSW_BulletManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "CSR_Player_Cody.h"
#include "Components/ArrowComponent.h"

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
	//NailHammerComp = CreateDefaultSubobject<UBoxComponent> ( TEXT ( "NailHammerComp" ) );
	//NailHammerComp->SetupAttachment ( RootComponent );
	//NailHammerComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
	//NailHammerComp->SetBoxExtent ( FVector ( 50.f ) );


}

// Called when the game starts or when spawned
void AHSW_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentHit.AddDynamic( this , &AHSW_Bullet::OnMyWallHit );

	//Player = GetWorld ( )->GetFirstPlayerController ( )->GetPawn ( );

	GetWorld ( )->GetTimerManager ( ).SetTimer ( TimerHandle , this , &AHSW_Bullet::LoadSecondPlayer , 0.1f , false );
	
	/*NailBagSocketAttach ( );*/
	//GetWorld ( )->GetTimerManager ( ).SetTimer ( TimerHandle , this , &AHSW_Bullet::NailBagSocketAttach , 0.1f , false );

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
	case ENailState::LOAD:			TickLoad ( DeltaTime );				break;
	case ENailState::SHOOT:			TickShoot ( DeltaTime );			break;
	case ENailState::EMBEDDED:		TickEmbedded ( DeltaTime );			break;
	case ENailState::UNEMBEDDED:	TickUnembedded ( DeltaTime );		break;
	case ENailState::RETURNING:		TickReturning ( DeltaTime );		break;
	case ENailState::GOTOBAG:		TickGoToBag ( DeltaTime );			break;
	}
}

void AHSW_Bullet::OnMyWallHit ( UPrimitiveComponent* HitComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit )
{
	// NailTag를 가진 컴포넌트와 부닥친다면
	if ( OtherComp->ComponentHasTag ( TEXT ( "NailTag" ) ) )
	{


		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "CollisionHit" ) );
		// TargetComp를 OtherComp로 맞추고싶다.
		TargetComp = OtherComp;
		NailBag->NailOutPush ( this);
		SetState ( ENailState::EMBEDDED );
		SetActorRotation((TargetComp->GetUpVector()).Rotation());

	}
// 	else if ( OtherActor->ActorHasTag ( TEXT ( "Wall1" ) ) )
// 	{
// 		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Red , TEXT ( "Wall1" ) );
// 		SetState ( ENailState::EMBEDDED );
// 	}
	//else if ( OtherActor->ActorHasTag ( TEXT ( "Wall2" ) ) )
	//{
	//	State = ENailState::UNEMBEDDED;
	//}
	else
	{
		//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Unembedded" ) );
		//NailBag->NailOutPush ( this );
		SetState(ENailState::UNEMBEDDED);
	}
}


void AHSW_Bullet::TickBasic ( const float& DeltaTime )
{

	// 못통에 붙어있는 기본상태
	// 못을 못통의 소켓의 위치로 이동시키고 싶다.
	SocketTransform = NailBag->MeshComp->GetSocketTransform ( SocketName );
	SetActorLocation ( SocketTransform.GetLocation ( ) );
	SetActorRotation ( SocketTransform.GetRotation ( ) );
	//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "State: Basic" ) );
	
	// 조건
	// 만약, 장전 상태가 된다면 State를 Load로 바꾸고싶다.
// 	if ( bIsLoading )
// 	{
// 		SetState(ENailState::LOAD);
// 	}
// 	else if ( bIsShooting )
// 	{
// 		SetState ( ENailState::SHOOT );
// 	}

}

void AHSW_Bullet::TickLoad ( const float& DeltaTime )
{
	//못의 위치를 플레이어의 손 소켓의 위치로 이동시키고싶다.
// 	SocketTransform = Player->FindComponentByClass<USkeletalMeshComponent> ( )->GetSocketTransform ( SocketName );
// 	SetActorLocation ( SocketTransform.GetLocation ( ) );
// 	SetActorRotation ( SocketTransform.GetRotation ( ) );
	
	//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Red , this->GetName ( ));
	//SetActorLocation ( Cast<ACSR_Player_Cody> ( Player )->ArrowComp->GetComponentLocation ( ) );
	//SetActorRotation ( Cast<ACSR_Player_Cody> ( Player )->ArrowComp->GetComponentRotation ( ) );
	//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Red , FString::Printf(TEXT ( " % f % f % f " ) , this->GetActorLocation ( ).X , this->GetActorLocation ( ).Y , this->GetActorLocation ( ).Z ));
	//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Red , TEXT ( "State: Load" ) );
	// 조건
	// 만약, 발사 상태가 된다면 State를 Load로 바꾸고 싶다.
// 	if ( bIsShooting )
// 	{
// 		SetState ( ENailState::SHOOT );
// 	}
// 	// 만약, 장전 해제가 된다면 State를 Basic으로 바꾸고싶다.
// 	if ( bBasic )
// 	{
// 		SetState ( ENailState::BASIC );
// 	}
}

void AHSW_Bullet::TickShoot ( const float& DeltaTime )
{
	//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "SHOOOOOOOT" ) );

	// 시작지점에서 끝지점까지 발사를 하고싶다.
	FVector dir =  EndPoint - StartPoint ;
	dir.Normalize ( );
	SetActorLocation (GetActorLocation() + dir* Speed * DeltaTime, true);
	FRotator rot = FRotationMatrix::MakeFromX ( dir ).Rotator ( );
	SetActorRotation ( rot );

	// 4초가 지나면 자동으로 돌아오게 하고싶다.
	CurrentTime += DeltaTime;
	if ( CurrentTime > BackTime )
	{
		SetState ( ENailState::RETURNING );
	}
// 	// 만약 E키가 눌려서 bIsReturning이 true가 된다면
// 	else if ( bIsReturning == true )
// 	{
// 		SetState ( ENailState::RETURNING );
// 	}
}

void AHSW_Bullet::TickEmbedded ( const float& DeltaTime )
{
	// To Do
	// TargerComponent의 위치에 고정시키고싶다.
	//SetActorLocation ( TargetComp->GetComponentLocation());
	//SetActorRotation ( TargetComp->GetComponentRotation( ) );

	// 조건
	// 플레이어가 E키를 누르면
// 	if ( bIsReturning )
// 	{
// 		DetachFromActor ( FDetachmentTransformRules::KeepWorldTransform );
// 		//	Returning 상태로 변경
// 		SetState ( ENailState::RETURNING );
// 	}
}

void AHSW_Bullet::TickUnembedded ( const float& DeltaTime )
{

	// To Do
	// 벽에서 튕겨나가고 싶다.
	// 
	// 조건
	// 4초가 지나면 자동으로 돌아오게 하고싶다.
	CurrentTime += DeltaTime;
	if ( CurrentTime > BackTime )
	{
		SetState ( ENailState::RETURNING );
	}

}

void AHSW_Bullet::TickReturning ( const float& DeltaTime )
{
	//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Return" ) );


	// To Do
	// 플레이어에게 돌아가고싶다
	//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Magenta , this->GetName ( ) );
	//Player를 Arrow 컴프로 설정해주기
	ReturnDir = Player->GetActorLocation() - this->GetActorLocation();
	Distance = (Player->GetActorLocation() - this->GetActorLocation ( )).Size();
	SetActorLocation ( FMath::Lerp(this->GetActorLocation(), Player->GetActorLocation(), 0.9f ));

	//SetActorLocationAndRotation ( FMath::Lerp ( this->GetActorLocation ( ) , nailDestLocation , 0.1 ) , FMath::Lerp ( this->GetActorRotation ( ) , nailDestRotation , 0.1 ) );



	//UE_LOG ( LogTemp , Warning , TEXT ( "%f" ),Distance );
	// 조건
	// 플레이어에게 도착하면 
	if ( Distance < NailDefaultDist )
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 1)->PlayerCameraManager->StartCameraShake(NailReturnCameraShake);
	//	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "End" ) );
		//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "Auto Return" ) );
		NailBag->NailPush ( this );
// 		bIsReturning = false;
		// Basic상태로 변경.
		SetState ( ENailState::BASIC );
	}
	
}


void AHSW_Bullet::TickGoToBag ( const float& DeltaTime )
{
	SetSocketName ( );
}

void AHSW_Bullet::SetState ( ENailState NextState)
{
	State = NextState;
	
	switch ( State )
	{
	case ENailState::BASIC:
		MovementComp->ProjectileGravityScale = 0;	
		MovementComp->bShouldBounce = false;

		//MeshComp->SetVisibility ( true );
		BoxComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
		//NailHammerComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );

		NailBasic ( );
		break;

	case ENailState::LOAD:
		//UGameplayStatics::PlaySound2D(GetWorld(), NailLoadSFV);
		NailLoad ( );
		break;

	case ENailState::SHOOT:
		//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Magenta , this->GetName ( ) );
		CurrentTime = 0;

		BoxComp->SetCollisionEnabled ( ECollisionEnabled::QueryAndPhysics );

		NailShoot ( );
		break;

	case ENailState::EMBEDDED:
		//UGameplayStatics::PlaySound2D(GetWorld(), NailEmbeddedSFV);
		UGameplayStatics::GetPlayerController(GetWorld(), 1)->PlayerCameraManager->StartCameraShake(NailShootCameraShake);
		MovementComp->bShouldBounce = false;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NailEmbeddedVFXFactory, MeshComp->GetSocketTransform(TEXT("NailVFXSocket")));

		//NailHammerComp->SetCollisionEnabled ( ECollisionEnabled::QueryOnly );
		NailEmbedded ( );
		break;

	case ENailState::UNEMBEDDED:
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NailEmbeddedVFXFactory, MeshComp->GetSocketTransform(TEXT("NailVFXSocket")));

		//UGameplayStatics::PlaySound2D(GetWorld(), NailUnEmbeddedSFV);
		BoxComp->SetEnableGravity ( true);
		MovementComp->bShouldBounce = true;
		MovementComp->ProjectileGravityScale = 1.f;
		break;

	case ENailState::RETURNING:
		//UGameplayStatics::PlaySound2D(GetWorld(), NailReturnSFV);
		BoxComp->SetEnableGravity ( false );
		BoxComp->SetCollisionEnabled ( ECollisionEnabled::QueryOnly );

		MovementComp->bShouldBounce = false;
		MovementComp->ProjectileGravityScale = 0;

		//NailHammerComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
		NailReturn ( );
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

void AHSW_Bullet::SetSocketName()
{
	// Nail이 들어갈 소켓 이름을 가져온다.
	FString socketNameString = FString::Printf ( TEXT ( "NailBag_%d" ) , NailBag->Magazine.Num ( ) -1);
	SocketName = FName( *socketNameString );
	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , socketNameString );


	// 해당 소켓이름에 맞는 곳에 attach 한다.
	// AttachToActor ( NailBag , FAttachmentTransformRules::SnapToTargetNotIncludingScale , SocketName );
}

void AHSW_Bullet::SetNailBag ( AHSW_BulletManager* nailBag )
{
	NailBag = nailBag;
}

void AHSW_Bullet::NailBasic ( )
{
	// 못 통에서 BeginPlay에서 스폰될때 호출됨
	// Nail이 Return될때 거리가 가까워지면 호출됨

	//만약 플레이어에 Attach되어있다면, Detach하고싶다.
	if ( this->IsAttachedTo ( Player ) )
	{
		this->DetachFromActor ( FDetachmentTransformRules::KeepWorldTransform );
	}
	SetSocketName ( );
	AttachToActor ( NailBag , FAttachmentTransformRules::KeepRelativeTransform , SocketName );
	// 못통의 소켓에 하고싶다.
	//NailBagSocketAttach ( );

	bBasic = true;
	bIsLoading = false;
	bIsShooting = false;

}

void AHSW_Bullet::NailLoad ( )
{

	// NailBag에서 Detach하고 
	DetachFromActor ( FDetachmentTransformRules::KeepRelativeTransform );
	// Player의 Arrow에 Attach하고싶다.
	AttachToComponent ( Cast<ACSR_Player_Cody> ( Player )->ArrowComp , FAttachmentTransformRules::KeepRelativeTransform );

	//AttachToComponent ( Cast<ACSR_Player_Cody>(Player)->ArrowComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
	bBasic = false;
	bIsLoading = true;

// 	USkeletalMeshComponent* Mesh = Player->FindComponentByClass<USkeletalMeshComponent> ( );
// 
// 	FTransform t = Mesh->GetSocketTransform ( socketName );
// 	SetActorLocation ( t.GetLocation ( ) );
// 	SetActorRotation ( Player->GetActorTransform().GetRotation ( ) );

}

void AHSW_Bullet::NailShoot ( )
{
	// 마우스 좌 클릭시 호출 됨.

// 	// 만약 못이 Player나 NailBag에 Attach되어있다면
	if ( IsAttachedTo ( Player ) || IsAttachedTo ( NailBag ) )
	{
	 	this->DetachFromActor ( FDetachmentTransformRules::KeepWorldTransform );
	}

	// 기본 상태에서 좌클릭
	bBasic = false;
	// 장전 상태에서 좌클릭
	bIsLoading = false;
	// Shooting상태로 변경 -> Tick Basic 혹은 Tick Load에서 SetState (Shoot)발동!
	bIsShooting = true;
}

void AHSW_Bullet::NailEmbedded ( )
{
	// NailTag를 가진 Component와 부딪혔을때 호출하는 함수

	// TargetComp에 Attach 하고싶다.
	AttachToComponent ( TargetComp , FAttachmentTransformRules::KeepWorldTransform );

	//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Embedded Attach!" ) );

	// 슈팅 상태에서 충돌일어나면 false
/*	bIsShooting = false;*/

}

void AHSW_Bullet::NailReturn ( )
{
	// Shoot, UnEmbedded에서 3초가 지나면 호출된다.
	// Shoot, Embedded, UnEmbedded에서 bIsReturning이 true가 되면 호출된다.
	// 
	// TargetComp이 있으면서 TargetComp에 붙어있다면

	if (TargetComp && this->IsAttachedTo ( TargetComp->GetOwner ( ) ))
	{
		// Detach하고싶다.
		this->DetachFromActor ( FDetachmentTransformRules::KeepWorldTransform );
	}
/*	bIsShooting = false;*/
}


void AHSW_Bullet::LoadSecondPlayer ( )
{
	APlayerController* SecondPlayerController = UGameplayStatics::GetPlayerController ( GetWorld ( ) , 1 );
	Player = Cast<ACSR_Player_Cody> ( SecondPlayerController->GetPawn ( ) );
	if ( Player == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT("Player nullptr !!!!!" ));
	}

}

void AHSW_Bullet::SetbIsReturning ( bool value )
{
	bIsReturning = value;
}

void AHSW_Bullet::FirstAttach ( FTransform t )
{

}

void AHSW_Bullet::SetStartAndEnd ( FVector start , FVector end )
{
	//Nail의 StartPoint와 EndPoint를 설정해줌. ( Lay의 Start와 End가 들어올 것이다.)
	StartPoint = start;
	EndPoint = end;
}
