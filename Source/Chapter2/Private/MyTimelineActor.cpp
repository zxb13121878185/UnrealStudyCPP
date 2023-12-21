// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTimelineActor.h"

// Sets default values
AMyTimelineActor::AMyTimelineActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建默认对象
	Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>tempStactiMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Door.SM_Door'"));
	if (tempStactiMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(tempStactiMesh.Object);
	}

	RootComponent = Scene;
	StaticMesh->SetupAttachment(Scene);
	Box->SetupAttachment(Scene);
	Box->SetBoxExtent(FVector(100, 100, 100));
	//Box->SetRelativeLocation(FVector())
}

// Called when the game starts or when spawned
void AMyTimelineActor::BeginPlay()
{
	Super::BeginPlay();

	TimelineDelegate.BindUFunction(this, TEXT("TimelineStart"));
	FinishedDelagate.BindUFunction(this, TEXT("TimelineFinished"));
	//设置浮点曲线
	Timeline->AddInterpFloat(CurveFloat, TimelineDelegate);
	Timeline->SetLooping(true);
	Timeline->PlayFromStart();
	Timeline->Play();
	Timeline->SetTimelineFinishedFunc(FinishedDelagate);

	//给碰撞添加处理函数
	Box->OnComponentBeginOverlap.AddDynamic(this, &AMyTimelineActor::BeginOverlapFunc);
	Box->OnComponentEndOverlap.AddDynamic(this, &AMyTimelineActor::EndOverlapFunc);
}

// Called every frame
void AMyTimelineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyTimelineActor::TimelineStart(float valuee)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Timeline Play:%f"), valuee));
	//旋转,绕着固定轴插值旋转
	float tempYawRot = FMath::Lerp(0, 90, valuee);
	StaticMesh->SetRelativeRotation(FRotator(0, tempYawRot, 0));
}

void AMyTimelineActor::TimelineFinished()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Timeline Finished"));
}

void AMyTimelineActor::BeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter1* tempCharater = Cast<AMyCharacter1>(OtherActor);
	if (tempCharater)
	{
		Timeline->PlayFromStart();
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("BeginOverLapEvent is success"));
}

void AMyTimelineActor::EndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	AMyCharacter1* tempCharater = Cast<AMyCharacter1>(OtherActor);
	if (tempCharater)
	{
		Timeline->ReverseFromEnd();//从后面往前播放
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("EndOverLapEvent is success"));
}
