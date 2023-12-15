// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 *
 */
UCLASS()
class CHAPTER2_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//这里设定的“buttonStart"按钮名称后面创建蓝图类UI中按钮的名称和这个一样
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonStart;
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonQuit;
	//进度条
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP")
	float CurHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP")
	float MaxHealth = 100.0f;


public:

	virtual bool Initialize()override;

public:

	UFUNCTION()
	void BtnClick_Start();
	UFUNCTION()
	void BtnClick_Quit();

	void UpdateHealth();
};
