// Fill out your copyright notice in the Description page of Project Settings.


#include "MySoftRefActor.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

// Sets default values
AMySoftRefActor::AMySoftRefActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMySoftRefActor::BeginPlay()
{
	Super::BeginPlay();

	FSoftObjectPath tempPath1 = TEXT("/Script/Engine.Texture2D'/Game/StarterContent/Textures/T_Burst_M.T_Burst_M'");
	//异步加载1
	//AsyStreamhandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(tempPath1);
	//if (AsyStreamhandle)
	//{
	//	UTexture2D* tempTex = Cast<UTexture2D>(AsyStreamhandle->GetLoadedAsset());
	//	if (tempTex)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("TexName:%s"), *tempTex->GetName()));
	//	}
	//}
	////同步加载
	//FSoftObjectPath tempPath2 = TEXT("/Script/Engine.Texture2D'/Game/StarterContent/Textures/T_Wood_Oak_D.T_Wood_Oak_D'");
	//TSharedPtr<FStreamableHandle> SynStreamhandle = UAssetManager::GetStreamableManager().RequestSyncLoad(tempPath2);
	//if (SynStreamhandle)
	//{
	//	UTexture2D* tempTex2 = Cast<UTexture2D>(SynStreamhandle->GetLoadedAsset());
	//	if (tempTex2)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("TexName:%s"), *tempTex2->GetName()));
	//	}
	//}

	AsyStreamhandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(tempPath1, FStreamableDelegate::CreateUObject(this, &AMySoftRefActor::AysLoadCallBack));
}



// Called every frame
void AMySoftRefActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMySoftRefActor::AysLoadCallBack()
{
	if (AsyStreamhandle)
	{
		UTexture2D* tempTex = Cast<UTexture2D>(AsyStreamhandle->GetLoadedAsset());
		if (tempTex)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("TexName:%s"), *tempTex->GetName()));
		}
	}
}

