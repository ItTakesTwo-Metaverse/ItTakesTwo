//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "TriggerCinematicPhase2.h"
//#include "Components/BoxComponent.h"
//#include "MovieSceneSequencePlaybackSettings.h"
//#include "LevelSequencePlayer.h"
//#include "LevelSequenceActor.h"
//#include "UObject/ConstructorHelpers.h"
//
//ATriggerCinematicPhase2::ATriggerCinematicPhase2 ( )
//{
//	PrimaryActorTick.bCanEverTick = true;
//
//	Trigger = CreateDefaultSubobject <UBoxComponent>(TEXT("Trigger" ) );
//	Trigger->SetBoxExtent(FVector(10.f, 10.f , 10.f ));
//	Trigger->SetCollisionProfileName(TEXT("Trigger" ));
//	RootComponent = Trigger;
//
//	// 멤버 변수 초기화
//	LevelSequence = nullptr;
//	LevelSequencePlayer = nullptr;
//	LevelSequenceActor = nullptr;
//
//	//LevelSequence = CreateDefaultSubobject <ULevelSequence>(TEXT("LevelSequence" ));
//
//	static ConstructorHelpers::FObjectFinder<ULevelSequence> LS(TEXT("/Script/LevelSequence.LevelSequence'/Game/LHM_Boss/LevelSequence/2Phage.2Phage'" ) );
//	if ( LS.Succeeded ( ) )
//	{
//		LevelSequence = LS.Object;
//	}
//	else
//	{
//		UE_LOG ( LogTemp , Error , TEXT ( "Failed to load LevelSequence" ) );
//	}
//
//}
//
//void ATriggerCinematicPhase2::BeginPlay ( )
//{
//	Super::BeginPlay ( );
//
//	// LevelSequenceActor를 월드에 스폰
//	if ( LevelSequence )
//	{
//		FMovieSceneSequencePlaybackSettings Settings;
//		Settings.bAutoPlay = false;
//		Settings.bPauseAtEnd = true;
//	
//		LevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>( ALevelSequenceActor::StaticClass ( ) );
//	
//		if ( LevelSequenceActor )
//		{
//			LevelSequenceActor->SetOwner(this); // 소유자 설정
//			LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer (GetWorld(), LevelSequence, Settings , LevelSequenceActor);
//			
//			if ( !LevelSequencePlayer )
//			{
//				UE_LOG ( LogTemp , Error , TEXT ( "Failed to create LevelSequencePlayer" ) );
//			}
//		}
//		else
//		{
//			UE_LOG ( LogTemp , Error , TEXT ( "Failed to spawn LevelSequenceActor" ) );
//		}
//	}
//	else
//	{
//		UE_LOG ( LogTemp , Error , TEXT ( "LevelSequence is null in BeginPlay" ) );
//	}
//
//}
//
//void ATriggerCinematicPhase2::Tick ( float DeltaTime )
//{
//	Super::Tick( DeltaTime );
//}
//
//void ATriggerCinematicPhase2::NotifyActorBeginOverlap ( AActor* OtherActor )
//{
//	Super::NotifyActorBeginOverlap(OtherActor);
//
//	if ( LevelSequence )
//	{
//		LevelSequencePlayer->Play( );
//	}
//	else
//	{
//		UE_LOG ( LogTemp , Error , TEXT ( "LevelSequencePlayer is null during overlap" ) );
//	}
//}


