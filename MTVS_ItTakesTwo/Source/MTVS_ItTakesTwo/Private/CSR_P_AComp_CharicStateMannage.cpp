// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_P_AComp_CharicStateMannage.h"


// Sets default values for this component's properties
UCSR_P_AComp_CharicStateMannage::UCSR_P_AComp_CharicStateMannage()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UCSR_P_AComp_CharicStateMannage::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UCSR_P_AComp_CharicStateMannage::CanChangeState ( int32 NewState )
{	
	switch ( NewState )
	{
		case IDLE:
			break;
		case MOVE:
			break;
		case RUN:
			break;
		case AIRMOVE:
			break;
		case SIT:
			break;
		case AIRSIT:
			break;
		case JUMP:
			break;
		case SCJUMP:
			break;
		case DASH:
			break;
		case DAMAGED:
			break;
		case PRESS:
			break;
		case DIE:
			break;
	}
	return true;
}

void UCSR_P_AComp_CharicStateMannage::ChangeState ( int32 NewState )
{
	this->CurrentState |= NewState;
}

void UCSR_P_AComp_CharicStateMannage::RemoveState ( int32 DeleteState )
{
	this->CurrentState &= ~DeleteState;
}

bool UCSR_P_AComp_CharicStateMannage::CanChangeMove ( )
{
	if(this->CurrentState & (AIRMOVE | AIRSIT | JUMP | SCJUMP | DASH | DAMAGED | PRESS | DIE))
		return false ;
	return true;
}
