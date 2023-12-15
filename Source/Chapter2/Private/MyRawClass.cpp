// Fill out your copyright notice in the Description page of Project Settings.


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


