// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_Direction_GameInstance.h"

// 캐릭터의 8방향 벡터입니다.
void UCSR_Direction_GameInstance::Init ( )
{
	Super::Init( );
	// 정면
	Directions.Add ( FVector2D ( 1.0f , 0.0f ) );

	// 우측
	Directions.Add ( FVector2D ( 0.0f , 1.0f ) );

	// 후면
	Directions.Add ( FVector2D ( -1.0f , 0.0f ) );

	// 좌측
	Directions.Add ( FVector2D ( 0.0f , -1.0f ) );

	// 45도
	Directions.Add ( FVector2D ( 1.0f , 1.0f ).GetSafeNormal() );

	// 135도
	Directions.Add ( FVector2D ( 1.0f , -1.0f ).GetSafeNormal ( ) );

	// 225도
	Directions.Add ( FVector2D ( -1.0f , -1.0f ).GetSafeNormal ( ) );

	// 315도
	Directions.Add ( FVector2D ( -1.0f , 1.0f ).GetSafeNormal ( ) );


}
