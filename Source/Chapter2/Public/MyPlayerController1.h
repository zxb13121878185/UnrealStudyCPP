// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController1.generated.h"

/**
 *
 */
UCLASS()
class CHAPTER2_API AMyPlayerController1 : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent();
	void WheelUpFunction();
	void WheelDownFunction();
	virtual void BeginPlay()override;
};
