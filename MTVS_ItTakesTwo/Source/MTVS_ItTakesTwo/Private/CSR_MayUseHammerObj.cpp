// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_MayUseHammerObj.h"
#include "HSW_Hammer.h"
#include "Engine/EngineBaseTypes.h"
#include "CSR_FunctionLib.h"
#include "CSR_Player_May.h"

// Sets default values for this component's properties
UCSR_MayUseHammerObj::UCSR_MayUseHammerObj()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}

// Called when the game starts
void UCSR_MayUseHammerObj::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FActorSpawnParameters parms;
	parms.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if ( this->GetWorld ( ) == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_MayUseHammerObj : this->GetWorld ( ) is null" ) );
	}
	this->Hammer = this->GetWorld ( )->SpawnActor<AHSW_Hammer> ( this->HammerFactory , parms );
	if ( this->Hammer == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_MayUseHammerObj : this->Hammer is null" ) );
	}
	
	this->Hammer->AttachToComponent ( (Cast<ACSR_Player_May>(GetOwner ( ))->HammerLocation) , FAttachmentTransformRules::SnapToTargetNotIncludingScale  );
	this->Hammer->SetActorRelativeRotation(FRotator(0.0f , 90.0f, 0.0f));

	
}

// Called every frame
void UCSR_MayUseHammerObj::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

void UCSR_MayUseHammerObj::Attack ( )
{

}

void UCSR_MayUseHammerObj::DetachHammer ( )
{
	this->Hammer->DetachFromActor ( FDetachmentTransformRules::KeepWorldTransform );
}

void UCSR_MayUseHammerObj::AttachHammer ( )
{
	this->Hammer->AttachToComponent ( (Cast<ACSR_Player_May> ( GetOwner ( ) )->HammerLocation) , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
	this->Hammer->SetActorRelativeRotation ( FRotator ( 0.0f , 90.0f , 0.0f ) );
}

