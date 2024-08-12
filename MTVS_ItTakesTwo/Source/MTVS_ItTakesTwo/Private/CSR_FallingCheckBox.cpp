// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_FallingCheckBox.h"
#include "Components/BoxComponent.h"

// Sets default values
ACSR_FallingCheckBox::ACSR_FallingCheckBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Box = CreateDefaultSubobject<UBoxComponent> (TEXT("Box") );
	this->Box->SetBoxExtent(FVector(50.0f));
}

// Called when the game starts or when spawned
void ACSR_FallingCheckBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACSR_FallingCheckBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

