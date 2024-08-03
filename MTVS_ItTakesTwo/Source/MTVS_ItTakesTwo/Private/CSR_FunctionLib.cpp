// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_FunctionLib.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "Engine/World.h"

// 입력한 tag를 가진 PlayerStart transform 정보를 반환합니다.
FTransform UCSR_FunctionLib::FindStartTransForm(UObject* InWorldObject, FString StartTag)
{
	if (InWorldObject == nullptr) {
		return (FTransform());
	}

	UWorld* World = InWorldObject->GetWorld();
	if (World == nullptr) {
		return (FTransform());
	}

	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStarts);
	for (AActor* Actor : PlayerStarts)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(Actor);
		if (PlayerStart && PlayerStart->PlayerStartTag == StartTag)
		{
			return PlayerStart->GetActorTransform();
		}
	}
	return (FTransform());
}

// 입력한 메세지를 로그에 출력하고 게임을 종료합니다.
void UCSR_FunctionLib::ExitGame(UWorld* world, FString str)
{
	if (world == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("UCSR_FunctionLib : world is null"));
	}
	UE_LOG(LogTemp, Error, TEXT("%s"), *str);
	UKismetSystemLibrary::QuitGame(world, nullptr, EQuitPreference::Quit, false);
}	

// float 매개변수를 abs하여 더한값을 리턴한다.
float UCSR_FunctionLib::SelectABSUpperFloat ( const float& a , const float& b )
{
	float ScaleValue_a = FMath::Abs<float> ( a );
	float ScaleValue_b = FMath::Abs<float> ( b );
	float TargetValue = ScaleValue_a + ScaleValue_b;
	return (TargetValue);
}
