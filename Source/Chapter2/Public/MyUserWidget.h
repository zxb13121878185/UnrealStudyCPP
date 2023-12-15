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

	//�����趨�ġ�buttonStart"��ť���ƺ��洴����ͼ��UI�а�ť�����ƺ����һ��
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonStart;
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonQuit;
	//������
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
