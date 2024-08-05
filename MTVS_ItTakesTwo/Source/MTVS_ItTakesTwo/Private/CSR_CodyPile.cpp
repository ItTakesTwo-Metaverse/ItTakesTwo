// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_CodyPile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CollisionQueryParams.h"
#include "CSR_PileInventory.h"
#include "HSW_Bullet.h"

// Sets default values for this component's properties
UCSR_CodyPile::UCSR_CodyPile()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	this->PileInven = CreateDefaultSubobject< UCSR_PileInventory> ( TEXT ( "PileInven" ) );
	
}


// Called when the game starts
void UCSR_CodyPile::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UCSR_CodyPile::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	if ( this->ExecToggle ) {
		//FVector target = LayCasting ( );
		//UE_LOG ( LogTemp , Warning , TEXT ( "%f %f %f" ) , target.X , target.Y , target.Z );
		this->InZooming(DeltaTime );
		this->CameraZoomInMoving( DeltaTime );
	}
	else {
		this->OutZooming(DeltaTime);
		this->CameraZoomOutMoving(DeltaTime);
	}

}

void UCSR_CodyPile::InitComp (UCameraComponent *CameraComp, USpringArmComponent *SpringArmComp, float ArmSpringDistance )
{
	this->CameraComp_ = CameraComp;
	this->SpringArmComp_ = SpringArmComp;
	this->InitArmSpringDistance = ArmSpringDistance;
}

void UCSR_CodyPile::ToggleButton ( bool ChangeToggle )
{
	this->ExecToggle = ChangeToggle;
}

void UCSR_CodyPile::InZooming ( float DetaTIme )
{
	//this->CameraComp_->FieldOfView = FMath::Lerp ( this->CameraComp_->FieldOfView , this->AfterCameraFov , DetaTIme * 3 );
	this->SpringArmComp_->TargetArmLength = FMath::Lerp( this->SpringArmComp_->TargetArmLength, this->AfterArmSpringDistance, DetaTIme * 10 );
}

void UCSR_CodyPile::OutZooming ( float DetaTIme )
{
	//this->CameraComp_->FieldOfView = FMath::Lerp ( this->CameraComp_->FieldOfView , this->InitCameraFov , DetaTIme );
	this->SpringArmComp_->TargetArmLength = FMath::Lerp ( this->SpringArmComp_->TargetArmLength , this->InitArmSpringDistance , DetaTIme * 4 );
}

void UCSR_CodyPile::CameraZoomInMoving ( float DetaTime )
{
	//this->SpringArmComp_->SocketOffset = FMath::Lerp( this->SpringArmComp_->SocketOffset , this->AfterArmOffsetLocation , DetaTime * 3 );
	this->SpringArmComp_->SetRelativeLocation(FMath::Lerp ( this->SpringArmComp_->GetRelativeLocation() , this->AfterArmOffsetLocation , DetaTime * 10 ));

}

void UCSR_CodyPile::CameraZoomOutMoving ( float DetaTime )
{
	//this->SpringArmComp_->SocketOffset  = FMath::Lerp ( this->SpringArmComp_->SocketOffset , this->InitArmOffsetLocation , DetaTime );
	this->SpringArmComp_->SetRelativeLocation ( FMath::Lerp ( this->SpringArmComp_->GetRelativeLocation ( ) , this->InitArmOffsetLocation , DetaTime * 4 ) );


}

FVector UCSR_CodyPile::LayCasting ( )
{
	FHitResult OutHit;
	FVector Start = this->CameraComp_->GetComponentLocation ( );
	FVector End = Start + this->CameraComp_->GetForwardVector ( ) * 100000.0f;
	ECollisionChannel TraceChannel = ECC_Visibility;
	FCollisionQueryParams Params;
	bool bHit = GetWorld ( )->LineTraceSingleByChannel ( OutHit , Start , End , TraceChannel , Params );
	if ( bHit != NULL ) {
		//DrawDebugLine ( GetWorld ( ) , Start , OutHit.ImpactPoint , FColor::Red , false , 3 );
		return (OutHit.Location);
	}
	return (FVector::ZeroVector);
}

void UCSR_CodyPile::OnMyActionFire (FVector startLocation , FRotator startRotation )
{
	UE_LOG ( LogTemp , Warning , TEXT ( "OnMyActionFire" ) );
	
	AHSW_Bullet *Nail = this->PileInven->NailPop( startLocation, startRotation );
	if ( Nail == nullptr ) {
		UE_LOG ( LogTemp , Warning , TEXT ( "Nail is empty" ) );
		return;
	}
	FVector target = LayCasting ( );
	UE_LOG(LogTemp, Error, TEXT("%f %f %f"), target.X, target.Y, target.Z);
	if ( target == FVector::Zero ( ) ) {
		UE_LOG ( LogTemp , Warning , TEXT ( "No target" ) );
		return;
	}
	Nail->StartPoint = startLocation;
	Nail->EndPoint = target;
	Nail->SetState ( ENailState::SHOOT );

}

void UCSR_CodyPile::OnMyActionBack ( )
{
	UE_LOG ( LogTemp , Warning , TEXT ( "OnMyActionBack" ) );
	this->PileInven->NailPush(nullptr );
}

