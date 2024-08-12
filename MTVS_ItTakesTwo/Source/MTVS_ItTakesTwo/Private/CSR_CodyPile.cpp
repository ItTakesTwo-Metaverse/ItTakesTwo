// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_CodyPile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CollisionQueryParams.h"
#include "CSR_PileInventory.h"
#include "HSW_Bullet.h"
#include "Blueprint/UserWidget.h"
#include "CSR_Player_Cody.h"
#include "Components/ArrowComponent.h"
#include "HSW_BulletManager.h"
#include "CSR_FunctionLib.h"

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

	FActorSpawnParameters parms;
	parms.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	this->NailBag = this->GetWorld ( )->SpawnActor<AHSW_BulletManager> ( this->NailBagFactory , parms );
	if ( this->NailBag == nullptr )
	{
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_MayUseHammerObj : this->NailBag is null" ) );
	}

	this->NailBag->AttachToComponent ( (Cast<ACSR_Player_Cody> ( GetOwner ( ) )->NailBagLocation) , FAttachmentTransformRules::SnapToTargetNotIncludingScale );

	// ...
	this->CrosshairUI = CreateWidget ( this->GetWorld ( ) , this->CrosshairUIFactory );
	if ( this->CrosshairUI ) {
		this->CrosshairUI->AddToViewport ( );
	}
	this->CrosshairUI->SetVisibility ( ESlateVisibility::Hidden );
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

void UCSR_CodyPile::InitComp (UCameraComponent *CameraComp, USpringArmComponent *SpringArmComp, float ArmSpringDistance, ACSR_Player_Cody * charic )
{
	this->CameraComp_ = CameraComp;
	this->SpringArmComp_ = SpringArmComp;
	this->InitArmSpringDistance = ArmSpringDistance;
	this->charic_ = charic;
}

void UCSR_CodyPile::ToggleButton ( bool ChangeToggle )
{	
	if ( ChangeToggle == true ) {
		this->CrosshairUI->SetVisibility ( ESlateVisibility::Visible );
		// 왜 안되는지 모름
		//this->CameraComp_->bUsePawnControlRotation = true;
		//this->charic_->bUseControllerRotationYaw = true;
	}
	else {
		this->CrosshairUI->SetVisibility ( ESlateVisibility::Hidden );
		// 왜 안되는지 모름
		//this->CameraComp_->bUsePawnControlRotation = false;
		//this->charic_->bUseControllerRotationYaw = false;
	}
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
	//FVector Start = this->CameraComp_->GetComponentLocation ( );
	FVector Start = this->charic_->ArrowComp->GetComponentLocation ( );
	//UE_LOG(LogTemp, Warning, TEXT(" % f % f % f "), this->CameraComp_->GetForwardVector ( ).X , this->CameraComp_->GetForwardVector ( ).Y, this->CameraComp_->GetForwardVector ( ).Z);
	FVector End = Start + this->charic_->ArrowComp->GetForwardVector ( ) * 100000.0f;
	ECollisionChannel TraceChannel = ECC_Visibility;
	FCollisionQueryParams Params;
	bool bHit = GetWorld ( )->LineTraceSingleByChannel ( OutHit , Start , End , TraceChannel , Params );
	if ( bHit != NULL ) {
		DrawDebugLine ( GetWorld ( ) , Start , OutHit.ImpactPoint , FColor::Red , false , 3 );
		return (OutHit.Location);
	}
	return (FVector::ZeroVector);
}

void UCSR_CodyPile::OnMyActionFire (FVector startLocation , FRotator startRotation, AHSW_Bullet* nail )
{
	UE_LOG ( LogTemp , Warning , TEXT ( "OnMyActionFire" ) );
	
	if ( nail == nullptr ) {
		UE_LOG ( LogTemp , Warning , TEXT ( "Nail is empty" ) );
		return;
	}
	FVector target = LayCasting ( );
	UE_LOG(LogTemp, Error, TEXT("%f %f %f"), target.X, target.Y, target.Z);
	if ( target == FVector::Zero ( ) ) {
		UE_LOG ( LogTemp , Warning , TEXT ( "No target" ) );
		return;
	}

	nail->NailShoot ( startLocation , target );

}

AHSW_Bullet* UCSR_CodyPile::OnMyActionBack ( )
{
	UE_LOG ( LogTemp , Warning , TEXT ( "OnMyActionBack" ) );
	AHSW_Bullet* bullet = this->NailBag->NailPush ( );
	if ( bullet == nullptr )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "NailPush returned nullptr!" ) );
		return nullptr;
	}
	else if ( NailBag== nullptr )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "NailBag nullptr!" ) );
		return nullptr;
	}
	return bullet;
}

