// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_P_AComp_CameraMove.h"
#include "CSR_P_Player.h"
#include "CSR_FunctionLib.h"

// Sets default values for this component's properties
UCSR_P_AComp_CameraMove::UCSR_P_AComp_CameraMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCSR_P_AComp_CameraMove::BeginPlay()
{
	Super::BeginPlay();

	// ...
	this->Character_ = Cast<ACSR_P_Player> ( this->GetOwner ( ) );
	if ( this->Character_ == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_P_AComp_CameraMove : this->Character_ is null" ) );
	}
	this->CharacterStateComp = this->Character_->CharacterStateComp;
	if ( this->CharacterStateComp == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_P_AComp_CameraMove : this->CharacterStateComp is null" ) );
	}
}


// Called every frame
void UCSR_P_AComp_CameraMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCSR_P_AComp_CameraMove::Player_View ( const FInputActionValue& Value )
{
	FVector2D V = Value.Get<FVector2D> ( );
	
	this->Character_->AddControllerYawInput ( -V.X );
	V.X = 0;
	this->Character_->AddControllerPitchInput ( V.Y );
	V.Y = 0;
}

