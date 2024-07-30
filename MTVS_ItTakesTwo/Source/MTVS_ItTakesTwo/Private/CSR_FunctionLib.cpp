// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_FunctionLib.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "Engine/World.h"

// �Է��� tag�� ���� PlayerStart transform ������ ��ȯ�մϴ�.
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

// �Է��� �޼����� �α׿� ����ϰ� ������ �����մϴ�.
void UCSR_FunctionLib::ExitGame(UWorld* world, FString str)
{
	if (world == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("UCSR_FunctionLib : world is null"));
	}
	UE_LOG(LogTemp, Error, TEXT("%s"), *str);
	UKismetSystemLibrary::QuitGame(world, nullptr, EQuitPreference::Quit, false);
}	
