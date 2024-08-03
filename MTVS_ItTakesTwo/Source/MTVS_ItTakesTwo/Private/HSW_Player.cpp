// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_Player.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "HSW_Bullet.h"

// Sets default values
AHSW_Player::AHSW_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHSW_Player::BeginPlay()
{
	Super::BeginPlay();
	
	auto* pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		UEnhancedInputLocalPlayerSubsystem* subSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subSys)
		{
			subSys->AddMappingContext(IMC_Player, 0);
		}
	}
}

// Called every frame
void AHSW_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHSW_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent> ( PlayerInputComponent );
	if ( input )
	{
		input->BindAction ( IA_Fire , ETriggerEvent::Started , this , &AHSW_Player::OnMyActionFire );
		input->BindAction ( IA_Back , ETriggerEvent::Started , this , &AHSW_Player::OnMyActionBack );
	}


}

void AHSW_Player::OnMyActionFire()
{
	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "FIre" ) );
	FTransform t = GetMesh()->GetSocketTransform ( TEXT ( "hand_r" ));
	Nail = GetWorld ( )->SpawnActor<AHSW_Bullet> ( NailFactory , t );
}

void AHSW_Player::OnMyActionBack ( )
{
	GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "Return" ) );
	Nail->State = Nail->SetStateReturning();
	if ( Nail->State == ENailState::RETURNING )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 2.0f , FColor::Yellow , TEXT ( "RETURNING" ) );
	}
}
