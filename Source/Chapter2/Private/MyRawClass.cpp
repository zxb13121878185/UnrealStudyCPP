// Fill out your copyright notice in the Description page of Project Settings.


//#include "DelegateActor.h"
#include "MyRawClass.h"

MyRawClass::MyRawClass()
{
}

MyRawClass::~MyRawClass()
{
}

void MyRawClass::RawStaticNoParamDelegateFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("RawStaticNoParamDelegateFunc")));
}

void MyRawClass::Raw_NoParamDelegateFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Raw_NoParamDelegateFunc")));
}

void MyRawClass::RawOneParamEventFunc(FString strVal)
{
	FString tempStr = FString("RawOneParamEventFunc");
	tempStr.Append(strVal);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, tempStr);
}