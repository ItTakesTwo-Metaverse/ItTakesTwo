// Fill out your copyright notice in the Description page of Project Settings.


#include "SCR_ItTakesTwoGameMode.h"
#include "CSR_FunctionLib.h"
#include "CSR_Player_Cody.h"
#include "CSR_Player_May.h"
#include "Kismet/GameplayStatics.h"

void ASCR_ItTakesTwoGameMode::BeginPlay()
{
	// �÷��̾� 0���� ��Ʈ�ѷ��� �����ɴϴ�.
	APlayerController *P1 = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (P1 == nullptr) {
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("ASCR_ItTakesTwoGameMode : P1 is Null"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}
	// �÷��̾� 1���� ��Ʈ�ѷ��� �����մϴ�.
	APlayerController* P2 = UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
	if (P2 == nullptr) {
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("ASCR_ItTakesTwoGameMode : P2 is Null"));
	}

	// PlayerStart transform ������ �����ɴϴ�.
	FTransform CodyTrans = UCSR_FunctionLib::FindStartTransForm(this, FString("Cody"));
	FTransform MayTrans = UCSR_FunctionLib::FindStartTransForm(this, FString("May"));


	// P1�� ������ May ĳ���͸� �����մϴ�.
	this->P1_May = GetWorld()->SpawnActor<ACSR_Player_May>(this->SpawnMay, MayTrans);
	if (this->P1_May == nullptr) {
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("ASCR_ItTakesTwoGameMode : P1_May is Null"));
	}
	// P1�� ��Ʈ�ѷ��� �����մϴ�.
	P1->Possess(this->P1_May);

	// P2�� ������ Cody ĳ���͸� �����մϴ�.
	this->P2_Cody = GetWorld()->SpawnActor<ACSR_Player_Cody>(this->SpawnCody, CodyTrans);
	if (this->P2_Cody == nullptr) {
		UCSR_FunctionLib::ExitGame(GetWorld(), FString("ASCR_ItTakesTwoGameMode : P2_Cody is Null"));
	}
	// P2�� ��Ʈ�ѷ��� �����մϴ�.
	P2->Possess(this->P2_Cody);
}
