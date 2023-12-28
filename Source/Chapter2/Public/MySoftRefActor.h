// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StreamableManager.h"
#include "MySoftRefActor.generated.h"

UCLASS()
class CHAPTER2_API AMySoftRefActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMySoftRefActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	/// <summary>
	/// class的是蓝图类，Object的可以是非类的资源如图片
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	FSoftObjectPath AssetObjectPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	FSoftClassPath AssetClassPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	TSoftObjectPtr<AActor> AssetObjectPtr;//场景中的物体
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	TSoftObjectPtr<AActor> AssetClassPtr;//场景中的物体
	TSharedPtr<FStreamableHandle>AsyStreamhandle;

	void AysLoadCallBack();
};
