// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameState1.h"
#include "MyHUD1.h"
#include "MyPawn1.h"
#include "MyPlayerController1.h"
#include "MyPlayerState1.h"
#include "MyGameMode1.generated.h"

/**
 *
 */
UCLASS()
class CHAPTER2_API AMyGameMode1 : public AGameMode
{
	GENERATED_BODY()
	AMyGameMode1();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//退出游戏或关卡切换的时候调用
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool varBool;
	int32 varInt32;
	int64 varInt64;
	float varFloat;
	BYTE varByte;
	FString varString;
	FName varName;
	FText varText;
	FVector varVector;
	FRotator varRotator;
	FTransform varTrans;

	//TArrary时动态数组，速度快、内存消耗小、安全性高，所有元素都为相同类型
	TArray<int>  MyArray;
	TMap<int32, int32> MyMap;
	TSet<FString> MySet;
	void PrintF();
	void PrintMap();
	void PrintSet();
};
