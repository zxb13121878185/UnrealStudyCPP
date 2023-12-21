// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor1.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyActor1::AMyActor1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region MyRegion

	//����

	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyScene"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
	MyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyParticle"));
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MyAudio"));
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));

	//���ø��Ӽ�
	RootComponent = MyScene;//��MyScene��ΪĬ�ϵĸ����
	MyMesh->SetupAttachment(MyScene);
	MyParticle->SetupAttachment(MyScene);
	MyAudio->SetupAttachment(MyScene);
	MyBox->SetupAttachment(MyScene);

	//��̬���ط�Ϊ��̬������Դ�;�̬������,��̬���ر����ڹ��캯����
	//��̬������Դ
	static ConstructorHelpers::FObjectFinder<UStaticMesh>TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe'"));
	MyMesh->SetStaticMesh(TempStaticMesh.Object);
	static ConstructorHelpers::FObjectFinder<UParticleSystem>TempParticle(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	MyParticle->SetTemplate(TempParticle.Object);
	static ConstructorHelpers::FObjectFinder<USoundWave>TempSoundWave(TEXT("/Script/Engine.SoundWave'/Game/StarterContent/Audio/Collapse01.Collapse01'"));
	MyAudio->SetSound(TempSoundWave.Object);

	////��̬������,�������ú��ļ�������������"_C",��Ȼ�����б���
	//static ConstructorHelpers::FClassFinder<AActor>TempMyActor(TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_WallSconce.Blueprint_WallSconce_C'"));
	//MyActor = TempMyActor.Class;//����������ֻ�����������Ҫͨ��SpawnActor��������ʵ��������Ϸ��

	//��ײ����
	//��ײ��������
	//MyBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MyBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//��ײ������������
	MyBox->SetCollisionObjectType(ECC_WorldDynamic);
	//��ײ��Ӧ
	MyBox->SetCollisionResponseToAllChannels(ECR_Overlap);//�������е�ͨ��
	//MyBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);//���õ���ͨ��

	//����Box�Ĵ�С
	MyBox->SetBoxExtent(FVector(64, 64, 64));

#pragma endregion

}

// Called when the game starts or when spawned
void AMyActor1::BeginPlay()
{
	Super::BeginPlay();
	if (MyParticle)
	{
		//������������������
		//MyParticle->Deactivate();
		MyParticle->SetActive(false);
	}

#pragma region Dynamic

	//if (MyActor)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("My Actor is:%s"), *MyActor->GetName());
	//	AActor* TempSpawnActor = GetWorld()->SpawnActor<AActor>(MyActor, FVector(100, 500, 100), FRotator::ZeroRotator);
	//}
	////��̬������Դ
	//UStaticMesh* TempStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	//if (TempStaticMesh)
	//{
	//	MyMesh->SetStaticMesh(TempStaticMesh);
	//}
	////��̬������
	//UClass* TempClass = LoadClass<AActor>(this, TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight_C'"));
	//if (TempClass)
	//{
	//	AActor* SpawanActor = GetWorld()->SpawnActor<AActor>(TempClass, FVector::ZeroVector, FRotator::ZeroRotator);
	//	UE_LOG(LogTemp, Warning, TEXT("Class Name:"), *TempClass->GetName());
	//}

#pragma endregion

	//����ײ��Ӵ�����
	MyBox->OnComponentBeginOverlap.AddDynamic(this, &AMyActor1::BeginOverlapFunc);
	MyBox->OnComponentEndOverlap.AddDynamic(this, &AMyActor1::EndOverlapFunc);
	MyBox->OnComponentHit.AddDynamic(this, &AMyActor1::HitFunc);
}

// Called every frame
void AMyActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//���������ƶ�
	FVector tempOffset = FVector(1, 0, 0);
	FHitResult tempHitResult;
	//AddActorLocalOffset(tempOffset, false, &tempHitResult);//���ڱ���������ƶ������ܵ��������Ӱ��
	AddActorWorldOffset(tempOffset * speedMove, false, &tempHitResult);//��������������ƶ��������ܵ��������Ӱ��

}



void AMyActor1::BeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//�Ƚ�������ײ����ת���ɽ�ɫ
	AMyCharacter1* tempCharacter = Cast<AMyCharacter1>(OtherActor);
	if (tempCharacter)
	{
		//Ӧ���˺�
		UGameplayStatics::ApplyDamage(tempCharacter, 5.0f, nullptr, this, UDamageType::StaticClass());
	}

	//MyParticle->Activate();
	MyParticle->SetActive(true);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("BeginOverLapEvent is success"));
}

void AMyActor1::EndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//MyParticle->Deactivate();
	MyParticle->SetActive(false);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("EndOverLapEvent is success"));
}

void AMyActor1::HitFunc(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Hit is :%s"), *OtherActor->GetName()));
	UE_LOG(LogTemp, Warning, TEXT("Hit is :%s"), *OtherActor->GetName());
}

