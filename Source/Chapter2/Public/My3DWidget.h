// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "My3DWidget.generated.h"

/**
 *
 */
UCLASS()
class CHAPTER2_API UMy3DWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My3DUI")
	float CurHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	float	MaxHealth = 100.0f;
};
