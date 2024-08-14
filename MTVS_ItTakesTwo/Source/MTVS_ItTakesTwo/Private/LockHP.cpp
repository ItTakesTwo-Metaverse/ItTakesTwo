// Fill out your copyright notice in the Description page of Project Settings.


#include "LockHP.h"
#include "Components/ProgressBar.h"

void ULockHP::NativeTick ( const FGeometry& MyGeometry , float InDeltaTime )
{
	Super::NativeTick ( MyGeometry , InDeltaTime );
}

void ULockHP::SetHPBar ( float cur , float max )
{
	HPBar->SetPercent ( cur / max );
}
