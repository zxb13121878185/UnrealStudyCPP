// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "MyObject1.generated.h"

USTRUCT(BlueprintType)
struct FMyObject1Data
{
	GENERATED_USTRUCT_BODY()
	FMyObject1Data();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyDataStruct")
	int32 Age;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyDataStruct")
	FString MyName;
};

UCLASS()
class CHAPTER2_API UMyObject1 : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FMyObject1Data MyData;

};
