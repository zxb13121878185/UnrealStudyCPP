// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn1.h"
#include "MyPlayerController1.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController1::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("WheelUp", IE_Pressed, this, &AMyPlayerController1::WheelUpFunction);
	InputComponent->BindAction("WheelDown", IE_Pressed, this, &AMyPlayerController1::WheelDownFunction);
}

void AMyPlayerController1::WheelUpFunction()
{
	if (GetPawn())
	{
		AMyPawn1* tempPawn = Cast<AMyPawn1>(GetPawn());
		if (tempPawn)
		{
			tempPawn->ZoomCam(1, 10);
		}
	}
}

void AMyPlayerController1::WheelDownFunction()
{
	if (GetPawn())
	{
		AMyPawn1* tempPawn = Cast<AMyPawn1>(GetPawn());
		if (tempPawn)
		{
			tempPawn->ZoomCam(0, 10);
		}
	}
}

void AMyPlayerController1::BeginPlay()
{
	Super::BeginPlay();
	//这里的参数NULL表示只是加载到场景中，不会加载到这个类下面
	//UClass* WidgetCalss = LoadClass<UUserWidget>(NULL, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UICPP.UICPP_C'"));
	//UUserWidget* MyWidgetClass = nullptr;
	//MyWidgetClass = CreateWidget<UUserWidget>(GetWorld(), WidgetCalss);
	//MyWidgetClass->AddToViewport();

}
