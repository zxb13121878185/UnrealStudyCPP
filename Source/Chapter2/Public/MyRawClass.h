// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "DelegateActor.h"
#include "CoreMinimal.h"

/**
 *
 */


class CHAPTER2_API MyRawClass
{
public:
	MyRawClass();
	~MyRawClass();

public:
	static void RawStaticNoParamDelegateFunc();
	void Raw_NoParamDelegateFunc();

	void RawOneParamEventFunc(FString strVal);

public:

};
