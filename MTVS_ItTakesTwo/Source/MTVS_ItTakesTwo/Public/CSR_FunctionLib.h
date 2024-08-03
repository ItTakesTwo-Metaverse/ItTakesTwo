// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CSR_FunctionLib.generated.h"

/**
 * 
 */
UCLASS()
class MTVS_ITTAKESTWO_API UCSR_FunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// 입력한 tag를 가진 PlayerStart transform 정보를 반환합니다.
	static FTransform FindStartTransForm(UObject* InWorldObject, FString StartTag);
	// 입력한 메세지를 로그에 출력하고 게임을 종료합니다.
	static void ExitGame(UWorld *world, FString str);
	// float 매개변수를 abs하여 더한값을 리턴한다.
	static float SelectABSUpperFloat (const float& a ,const float& b );
};
