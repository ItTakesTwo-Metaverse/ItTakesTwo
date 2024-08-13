// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_P_AComp_CharicStateMannage.h"
#include "cmath"
#include "CSR_BaseAnimation.h"
#include "CSR_FunctionLib.h"


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
		case ATTACK:
			return (CanAddAttack( ));
			break;
		case DAMAGED:
			return (CanAddDamaged ( ));
			break;
		case INVI:
			return (CanAddIniv ());
			break;
		case PRESS:
			return (CanAddPress ( ));
			break;
		case REBORN:
			return (CanAddReBorn ( ));
			break;
		case DIE:
			return (CanAddDie ( ));
			break;
	}
	return true;
}

bool UCSR_P_AComp_CharicStateMannage::AddState ( int32 NewState )
{
	if ( this->TotalControlState ( NewState ) ) {
		this->CurrentState = this->CurrentState | NewState;
		UE_LOG(LogTemp, Warning, TEXT("%d %d" ), this->CurrentState, NewState );
		this->SpendStateToAnim ( );
		return (true);
	}
	return (false);
}

void UCSR_P_AComp_CharicStateMannage::RemoveState ( int32 DeleteState )
{
	this->CurrentState &= ~DeleteState;
	this->SpendStateToAnim ( );
}

void UCSR_P_AComp_CharicStateMannage::SpendStateToAnim ( )
{
	int flag = this->CurrentState;
	int count = 0;
	while (flag != 0 && (flag & 1) == 0 ) {
		count = count + 1;
		flag = flag >> 1;
	}
	if ( count == 0 ) {
		this->Anim->CurrentType = 1;
	}
	this->Anim->CurrentType = (pow ( 2 , count ));
}

//void UCSR_P_AComp_CharicStateMannage::SetAnims ( class UCSR_BaseAnimation* NewAnim )
//{
//	this->Anim = NewAnim;
//	if ( this->Anim == nullptr ) {
//		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_P_AComp_CharicStateMannage is this->Anim  NULL" ) );
//	}
//}

bool UCSR_P_AComp_CharicStateMannage::CanAddMove ( )
{
	if ( this->CurrentState & (JUMPMOVE | AIRSIT | JUMP | SCJUMP | DASH | SIT | ATTACK | DAMAGED | PRESS | REBORN | DIE) ) {
		return false;
	}
	return true;
}

bool UCSR_P_AComp_CharicStateMannage::CanAddPress ( )
{
	if ( this->CurrentState & (DIE | REBORN )) {
		return false;
	}
	return true;
}

bool UCSR_P_AComp_CharicStateMannage::CanAddJumpMove ( )
{
	if ( this->CurrentState & (DIE | REBORN | PRESS | ATTACK | AIRSIT | MOVE) ) {
		return false;
	}
	if ( this->CurrentState & JUMP ) {
		return true;
	}
	return false;
}

bool UCSR_P_AComp_CharicStateMannage::CanAddJump ( )
{
	if ( this->CurrentState & (AIRSIT | SCJUMP | DAMAGED | ATTACK | REBORN | PRESS | DIE) ) {
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

bool UCSR_P_AComp_CharicStateMannage::CanAddDie ( )
{	
	this->CurrentState = DIE;
	return (true);
}

bool UCSR_P_AComp_CharicStateMannage::CanAddReBorn ( )
{
	if ( this->CurrentState & DIE ) {
		return (true);
	}
	return (false);
}

bool UCSR_P_AComp_CharicStateMannage::CanAddIniv ( )
{
	if ( this->CurrentState & (REBORN | DAMAGED )) {
		return (true);
	}
	return (false);
}

bool UCSR_P_AComp_CharicStateMannage::CanAddAttack ( )
{
	if ( this->CurrentState & (AIRSIT | SCJUMP | DAMAGED | ATTACK | REBORN | PRESS | DIE)) {
		return (false);
	}
	return (true);
}

bool UCSR_P_AComp_CharicStateMannage::CanAddDamaged ( )
{
	if ( this->CurrentState & (DIE | PRESS | REBORN | INVI) ) {
		return (false);
	}
	return (true);
}

