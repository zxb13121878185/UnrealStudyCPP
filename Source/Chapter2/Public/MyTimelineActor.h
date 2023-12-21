// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCharacter1.h"
#include "Components//BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "MyTimelineActor.generated.h"

UCLASS()
class CHAPTER2_API AMyTimelineActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyTimelineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
	UCurveFloat* CurveFloat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
	UTimelineComponent* Timeline;

	FOnTimelineFloat TimelineDelegate;//һ��ʼ�İ�
	FOnTimelineEvent FinishedDelagate;//���ʱ�İ�

	UFUNCTION()
	void TimelineStart(float valuee);
	UFUNCTION()
	void TimelineFinished();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
	USceneComponent* Scene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
	UBoxComponent* Box;


	//��ײ����
	UFUNCTION()
	void BeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
