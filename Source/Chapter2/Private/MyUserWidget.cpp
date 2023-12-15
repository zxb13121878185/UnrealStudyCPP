// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

bool UMyUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}


	ButtonStart->OnClicked.AddDynamic(this, &UMyUserWidget::BtnClick_Start);
	ButtonQuit->OnClicked.AddDynamic(this, &UMyUserWidget::BtnClick_Quit);

	return true;
}

void UMyUserWidget::BtnClick_Start()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Button Start"));
	UpdateHealth();
}

void UMyUserWidget::BtnClick_Quit()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Button Quit"));
}

void UMyUserWidget::UpdateHealth()
{
	if (CurHealth <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("血量不够!"));
	}
	else
	{

		CurHealth -= 10;
	}
}
