// Fill out your copyright notice in the Description page of Project Settings.


#include "SCR_ItTakesTwoGameMode.h"
#include "CSR_FunctionLib.h"
#include "CSR_Player_Cody.h"
#include "CSR_Player_May.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/LocalPlayer.h"
#include "CustomGameViewportClient.h"
#include "TimerManager.h"
#include "UObject/Object.h"
#include "../ToolboxBoss.h"

void ASCR_ItTakesTwoGameMode::InitGame ( const FString& MapName , const FString& Options , FString& ErrorMessage )
{
	Super::InitGame(MapName, Options, ErrorMessage	);
}

ASCR_ItTakesTwoGameMode::ASCR_ItTakesTwoGameMode ( )
{	
	
}

void ASCR_ItTakesTwoGameMode::SetMayDie ( bool flag )
{
	this->MayDie = flag;
	ChangeMaps ();
}

void ASCR_ItTakesTwoGameMode::SetCodyDie ( bool flag )
{
	this->CodyDie = flag;
	ChangeMaps ();
}

void ASCR_ItTakesTwoGameMode::ChangeMaps ( )
{
	if ( !this->MayDie && !this->CodyDie ) {
		this->MayCodyAllAliveMap();
	}
	else if ( this->MayDie && this->CodyDie ) {
		this->MayCodyAllDieMap();
	}
	else if ( this->MayDie ) {
		this->MayDieMap();
	}
	else if ( this->CodyDie ) {
		this->CodyDieMap();
	}
	else {
		this->CutSinMap();
	}
}

UCustomGameViewportClient* ASCR_ItTakesTwoGameMode::GetCustomViewportClient ( )
{
	return (this->CustomViewportClient);
}

void ASCR_ItTakesTwoGameMode::CallCutSin()
{
	this->P1_May->TranceSIn();
}

void ASCR_ItTakesTwoGameMode::BeginPlay()
{
	Super::BeginPlay ();

	// 플레이어 0번의 컨트롤러를 가져옵니다.
	APlayerController *P1 = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (P1 == nullptr) {
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("ASCR_ItTakesTwoGameMode : P1 is Null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}
	// 플레이어 1번의 컨트롤러를 생성합니다.
	APlayerController* P2 = UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
	if (P2 == nullptr) {
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("ASCR_ItTakesTwoGameMode : P2 is Null"));
	}

	// PlayerStart transform 정보를 가져옵니다.
	FTransform CodyTrans = UCSR_FunctionLib::FindStartTransForm(this, FString("Cody"));
	FTransform MayTrans = UCSR_FunctionLib::FindStartTransForm(this, FString("May"));


	// P1이 조종할 May 캐릭터를 스폰합니다.
	this->P1_May = GetWorld ( )->SpawnActor<ACSR_Player_May> ( this->SpawnMay , MayTrans );
	if ( this->P1_May == nullptr ) {
		UCSR_FunctionLib::ExitGame ( GetWorld ( ) , FString ( "ASCR_ItTakesTwoGameMode : P1_May is Null" ) );
	}
	// P1을 컨트롤러와 연결합니다.
	P1->Possess ( this->P1_May );

	// P2가 조종할 Cody 캐릭터를 스폰합니다.
	this->P2_Cody = GetWorld ( )->SpawnActor<ACSR_Player_Cody> ( this->SpawnCody , CodyTrans );
	if ( this->P2_Cody == nullptr ) {
		UCSR_FunctionLib::ExitGame ( GetWorld ( ) , FString ( "ASCR_ItTakesTwoGameMode : P2_Cody is Null" ) );
	}
	// P2을 컨트롤러와 연결합니다.
	P2->Possess ( this->P2_Cody );
	this->P1_May->GetMapMode(this);
	this->P2_Cody->GetMapMode(this);
	this->CustomViewportClient = Cast<UCustomGameViewportClient> ( GetWorld ( )->GetGameViewport ( ) );

	this->boss = Cast<AToolboxBoss>(UGameplayStatics::GetActorOfClass(this->GetWorld(), AToolboxBoss::StaticClass()));
	if (this->boss == nullptr) {
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("ASCR_ItTakesTwoGameMode : boss is Null"));
	}
	this->boss->GMMode = this;
}
