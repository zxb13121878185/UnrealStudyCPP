// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance1.generated.h"

/**
 *
 */
UCLASS()
class CHAPTER2_API UMyGameInstance1 : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance1();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyInstance")
	int32 IP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyInstance")
	FString UserName;
};
