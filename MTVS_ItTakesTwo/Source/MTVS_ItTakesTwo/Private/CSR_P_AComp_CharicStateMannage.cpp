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

bool UCSR_P_AComp_CharicStateMannage::TotalControlState ( int32 NewState )
{	
	switch ( NewState )
	{
		case IDLE:
			break;
		case MOVE:
			return (this->CanAddMove ());
		case JUMPMOVE:
			return (this->CanAddJumpMove());
			break;
		case RUN:
			return (this->CanAddRun( ));
			break;
		case AIRMOVE:
			break;
		case SIT:
			break;
		case AIRSIT:
			break;
		case JUMP:
			return (this->CanAddJump ( ));
			break;
		case SCJUMP:
			break;
		case DASH:
			break;
		case DAMAGED:
			break;
		case PRESS:
			return (CanAddPress ( ));
			break;
		case DIE:
			break;
	}
	return true;
}

bool UCSR_P_AComp_CharicStateMannage::AddState ( int32 NewState )
{
	if ( this->TotalControlState ( NewState ) ) {
		this->CurrentState |= NewState;
		return (true);
	}
	return (false);
}

void UCSR_P_AComp_CharicStateMannage::RemoveState ( int32 DeleteState )
{
	this->CurrentState &= ~DeleteState;
}

bool UCSR_P_AComp_CharicStateMannage::CanAddMove ( )
{
	if ( this->CurrentState & (AIRMOVE | AIRSIT | JUMP | SCJUMP | DASH | DAMAGED | PRESS | DIE) ) {
		return false;
	}
	return true;
}

bool UCSR_P_AComp_CharicStateMannage::CanAddPress ( )
{
	if ( this->CurrentState & DIE ) {
		return false;
	}
	return true;
}

bool UCSR_P_AComp_CharicStateMannage::CanAddJumpMove ( )
{
	if ( this->CurrentState & JUMP ) {
		return true;
	}
	return false;
}

bool UCSR_P_AComp_CharicStateMannage::CanAddJump ( )
{
	if ( this->CurrentState & (AIRSIT | SCJUMP | DAMAGED | PRESS | DIE) ) {
		return false;
	}
	return true;
}

bool UCSR_P_AComp_CharicStateMannage::CanAddRun ( )
{
	if ( this->CurrentState & (AIRSIT | SCJUMP | DAMAGED | PRESS | DIE | JUMP) ) {
		return false;
	}
	return true;
}

