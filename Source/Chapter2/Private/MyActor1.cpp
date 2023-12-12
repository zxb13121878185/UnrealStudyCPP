// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor1.h"

// Sets default values
AMyActor1::AMyActor1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region MyRegion
	//��̬����
	/*
	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyScene"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
	MyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyParticle"));
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MyAudio"));

	//���ø��Ӽ�
	RootComponent = MyScene;//��MyScene��ΪĬ�ϵĸ����
	MyMesh->SetupAttachment(MyScene);
	MyParticle->SetupAttachment(MyScene);
	MyBox->SetupAttachment(MyScene);
	MyAudio->SetupAttachment(MyBox);

	//��̬���ط�Ϊ��̬������Դ�;�̬������,��̬���ر����ڹ��캯����
	//��̬������Դ
	static ConstructorHelpers::FObjectFinder<UStaticMesh>TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe'"));
	MyMesh->SetStaticMesh(TempStaticMesh.Object);
	static ConstructorHelpers::FObjectFinder<UParticleSystem>TempParticle(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	MyParticle->SetTemplate(TempParticle.Object);
	static ConstructorHelpers::FObjectFinder<USoundWave>TempSoundWave(TEXT("/Script/Engine.SoundWave'/Game/StarterContent/Audio/Collapse01.Collapse01'"));
	MyAudio->SetSound(TempSoundWave.Object);

	//��̬������,�������ú��ļ�������������"_C",��Ȼ�����б���
	static ConstructorHelpers::FClassFinder<AActor>TempMyActor(TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_WallSconce.Blueprint_WallSconce_C'"));
	MyActor = TempMyActor.Class;//����������ֻ�����������Ҫͨ��SpawnActor��������ʵ��������Ϸ��
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
	//��̬������Դ
	UStaticMesh* TempStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	if (TempStaticMesh)
	{
		MyMesh->SetStaticMesh(TempStaticMesh);
	}
	//��̬������
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

