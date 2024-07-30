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
	// �Է��� tag�� ���� PlayerStart transform ������ ��ȯ�մϴ�.
	static FTransform FindStartTransForm(UObject* InWorldObject, FString StartTag);
	// �Է��� �޼����� �α׿� ����ϰ� ������ �����մϴ�.
	static void ExitGame(UWorld *world, FString str);
};
