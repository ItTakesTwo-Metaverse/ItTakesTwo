// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_Hammer.h"
#include "Components/BoxComponent.h"
#include "../Public/HSW_Bullet.h"
#include "HSW_Player_May.h"
#include "Components/SceneComponent.h"

// Sets default values
AHSW_Hammer::AHSW_Hammer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//충돌체
	BoxComp = CreateDefaultSubobject<UBoxComponent> ( TEXT ( "BoxComp" ) );
	SetRootComponent ( BoxComp );
	BoxComp->SetCollisionProfileName ( TEXT ( "Hammer" ) );


	//외형
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "MeshComp" ) );
	MeshComp->SetupAttachment ( RootComponent );
	MeshComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );

	//스켈레탈메시
	//HammerMesh = CreateDefaultSubobject<USkeletalMeshComponent> (TEXT ( "HammerMesh" ) );
	//HammerMesh->SetupAttachment(RootComponent);
	//HammerMesh->SetCollisionProfileName ( TEXT ( "Hammer" ) );

}

// Called when the game starts or when spawned
void AHSW_Hammer::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentHit.AddDynamic( this , &AHSW_Hammer::OnMyBoxHit );
	BoxComp->OnComponentBeginOverlap.AddDynamic ( this , &AHSW_Hammer::OnMyBoxBeginOverlap );
	BoxComp->OnComponentEndOverlap.AddDynamic ( this , &AHSW_Hammer::OnMyBoxEndOverlap );

	may = Cast<AHSW_Player_May>(GetWorld ( )->GetFirstPlayerController ( )->GetPawn ( ));
}

// Called every frame
void AHSW_Hammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if ( bMoveToNail )
	{
		MoveToNail ( DeltaTime );
	}
	//매달려 있다면
	else if ( bIsHanging )
	{
	//계속해서 진자운동 하고싶다.
		HammerRotation( DeltaTime );
		//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Rotating" ) );
	}

}

void AHSW_Hammer::OnMyBoxHit ( UPrimitiveComponent* HitComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit )
{
	//bullet = Cast<AHSW_Bullet> ( OtherActor );
//	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Hammer" ) );
	if ( bullet )
	{
		//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "Hammer and nail" ) );
	}
}

void AHSW_Hammer::OnMyBoxBeginOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	bCanHanging = true;
	bullet = Cast<AHSW_Bullet> ( OtherActor );
	//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "Begin Overlap" ) );
	if ( bullet )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "bullet exist" ) );
	}
}

void AHSW_Hammer::OnMyBoxEndOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex )
{
	bCanHanging = false;
	//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "End Overlap" ) );
	if ( (bMoveToNail == true && bIsHanging == false) || (bMoveToNail == false && bIsHanging == true) )
	{
		bullet = nullptr;
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "bullet null" ) );
	}
}

void AHSW_Hammer::ClickToMove ( )
{
	if ( bCanHanging )
	{
		bMoveToNail = true;
		bCanHanging = false;
	}
}

void AHSW_Hammer::MoveToNail ( float deltatime)
{
	
	if ( bullet )
	{
		//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , FString::Printf ( TEXT ( "invoke" ) ) );
		FVector currentLocation = this->GetActorLocation ( );
		FVector nailLocation = bullet->GetActorLocation ( );
		FString testString = FString::Printf ( TEXT ( "%f, %f, %f" ) , nailLocation.X , nailLocation.Y , nailLocation.Z );
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , testString);
		float distance = ( nailLocation - currentLocation).Size ( );
		FVector dir = (nailLocation-currentLocation).GetSafeNormal();
		SetActorLocation ( FMath::Lerp ( currentLocation , nailLocation , 0.05f ));
		//SetActorLocation ( currentLocation + dir * 500.f * deltatime );

		//GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , FString::Printf(TEXT ( "%f" ),distance ));
		if ( distance < 150 )
		{
			bIsHanging = true;
			bMoveToNail = false;
			GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , TEXT ( "Attach!" ) );

			//소켓의 위치와 회전을 가져온다.
			FTransform SocketTransform = bullet->MeshComp->GetSocketTransform ( TEXT ( "AttachingPoint" ) );

			//this->AttachToActor( bullet, FAttachmentTransformRules::SnapToTargetNotIncludingScale , TEXT ( "AttachingPoint" ) );
			this->AttachToActor( bullet, FAttachmentTransformRules::SnapToTargetIncludingScale );

			this->SetActorLocation ( SocketTransform.GetLocation ( ) );
			this->SetActorRotation ( SocketTransform.GetRotation());


		}
	}
	else
	{
		bIsHanging = false;
		bMoveToNail = false;
	}
}



void AHSW_Hammer::AttachHammerToNail ( )
{



}



void AHSW_Hammer::DetachHammerFromNail ( )
{
	bIsHanging = false;
	if ( bullet )
	{
		MeshComp->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		//auto* otherSceneComp = may->GetComponentByClass<USceneComponent> ( );
		//SetActorLocation ( otherSceneComp->GetComponentLocation ( ) );

// 		FString testString = FString::Printf ( TEXT ( "%f, %f, %f" ) , otherSceneComp->GetComponentLocation ( ).X , otherSceneComp->GetComponentLocation ( ).Y , otherSceneComp->GetComponentLocation ( ).Z );
// 		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Blue , testString );
		

	}
}

void AHSW_Hammer::HammerRotation (float DeltaTime )
{
	//현재 매쉬의 위치 가져오기
	//FVector CurrentLocation = MeshComp->GetComponentLocation ( );
	CurrentTime += DeltaTime;
	float Angle = Amplitude * FMath::Sin ( CurrentTime * Frequency * 2.0f * PI );

	FRotator newRotation = FRotator( 0.0f , 0.0f , Angle);
	this->SetActorRelativeRotation ( newRotation );
	//MeshComp->SetRelativeRotation ( newRotation );
}


FVector AHSW_Hammer::GetHammerSocketLocation ( )
{
	FVector socketLocation = MeshComp->GetSocketLocation ( TEXT ( "PlayerAttachingPoint" ) );
	return socketLocation;
}
