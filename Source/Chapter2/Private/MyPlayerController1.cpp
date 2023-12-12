// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn1.h"
#include "MyPlayerController1.h"

void AMyPlayerController1::SetupInputComponent()
{
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
