// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_PlayerWidget.h"
#include "TimerManager.h"
#include "Engine/World.h"

float UCSR_PlayerWidget::InitHPBar ( float HP )
{
	this->TargetHP = HP;
	this->MemoHP = HP;
	return (HP);
}

float UCSR_PlayerWidget::TakeDamage ( float CurHP , float MaxHP )
{
    this->TargetHP = CurHP;
	return(CurHP / MaxHP);
}


//void UCSR_PlayerWidget::TakeDelayDamage ( )
//{
//	GetWorld ( )->GetTimerManager ( ).SetTimer( TimerHandle , this , &UCSR_PlayerWidget::DecreaseDelayBar , 0.5f , true );
//}

float UCSR_PlayerWidget::DecreaseDelayBar ( FTimerHandle TimerHandle )
{
	this->MemoHP = this->MemoHP - 1;

	if ( this->MemoHP <= this->TargetHP )
	{
		this->GetWorld ( )->GetTimerManager ( ).ClearTimer ( TimerHandle );
	}
	
	return (this->MemoHP / 10);
}

