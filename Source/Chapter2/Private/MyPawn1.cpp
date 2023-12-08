// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn1.h"

// Sets default values
AMyPawn1::AMyPawn1()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn1::BeginPlay()
{
	Super::BeginPlay();
	//BlueprintNativeEvent1_Implementation();//如果用这个调用会执行C++的代码，不会执行蓝图中的功能
	//BlueprintNativeEvent1();//使用这个声明而不是上述带后缀_Implementation的方法可以实现蓝图被调用，而C++中的不会被调用

	//ImplementableEvent1();
	//ImplementableEvent2();
}

// Called every frame
void AMyPawn1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyPawn1::BlueprintCallable1()
{

}

bool AMyPawn1::BlueprintPure2()
{
	return false;
}


void AMyPawn1::BlueprintNativeEvent1_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("这是一个C++代码写的BlueprintNativeEvent事件"));
}

int32 AMyPawn1::BlueprintNativeEvent2_Implementation()
{
	return 0;
}

void AMyPawn1::BlueprintNativeEvent3_Implementation(const FString& myStr)
{

}

int32 AMyPawn1::BlueprintNativeEvent4_Implementation(const FString& myStr)
{
	return 0;
}

void AMyPawn1::PrintMeta()
{

}

