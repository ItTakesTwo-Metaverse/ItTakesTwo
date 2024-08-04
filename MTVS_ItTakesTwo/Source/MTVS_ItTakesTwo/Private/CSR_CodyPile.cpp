// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_CodyPile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UCSR_CodyPile::UCSR_CodyPile()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

