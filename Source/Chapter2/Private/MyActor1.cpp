// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor1.h"

// Sets default values
AMyActor1::AMyActor1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region MyRegion
	//动态加载
	/*
	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyScene"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
	MyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyParticle"));
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MyAudio"));

	//设置父子级
	RootComponent = MyScene;//将MyScene作为默认的根组件
	MyMesh->SetupAttachment(MyScene);
	MyParticle->SetupAttachment(MyScene);
	MyBox->SetupAttachment(MyScene);
	MyAudio->SetupAttachment(MyBox);

	//静态加载分为静态加载资源和静态加载类,静态加载必须在构造函数里
	//静态加载资源
	static ConstructorHelpers::FObjectFinder<UStaticMesh>TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe'"));
	MyMesh->SetStaticMesh(TempStaticMesh.Object);
	static ConstructorHelpers::FObjectFinder<UParticleSystem>TempParticle(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	MyParticle->SetTemplate(TempParticle.Object);
	static ConstructorHelpers::FObjectFinder<USoundWave>TempSoundWave(TEXT("/Script/Engine.SoundWave'/Game/StarterContent/Audio/Collapse01.Collapse01'"));
	MyAudio->SetSound(TempSoundWave.Object);

	//静态加载类,复制引用后，文件名后面必须加上"_C",不然会运行崩溃
	static ConstructorHelpers::FClassFinder<AActor>TempMyActor(TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_WallSconce.Blueprint_WallSconce_C'"));
	MyActor = TempMyActor.Class;//这样创建的只是在内容里，还要通过SpawnActor方法将它实例化到游戏里
	*/
#pragma endregion

}

// Called when the game starts or when spawned
void AMyActor1::BeginPlay()
{
	Super::BeginPlay();

#pragma region Dynamic Load
	/*
	if (MyActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("My Actor is:%s"), *MyActor->GetName());
		AActor* TempSpawnActor = GetWorld()->SpawnActor<AActor>(MyActor, FVector(100, 500, 100), FRotator::ZeroRotator);
	}
	//动态加载资源
	UStaticMesh* TempStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	if (TempStaticMesh)
	{
		MyMesh->SetStaticMesh(TempStaticMesh);
	}
	//动态加载类
	UClass* TempClass = LoadClass<AActor>(this, TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight_C'"));
	if (TempClass)
	{
		AActor* SpawanActor = GetWorld()->SpawnActor<AActor>(TempClass, FVector::ZeroVector, FRotator::ZeroRotator);
		UE_LOG(LogTemp, Warning, TEXT("Class Name:"), *TempClass->GetName());
	}
	*/
#pragma endregion
}

// Called every frame
void AMyActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

