// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor1.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyActor1::AMyActor1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region MyRegion

	//加载

	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyScene"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
	MyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyParticle"));
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MyAudio"));
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));

	//设置父子级
	RootComponent = MyScene;//将MyScene作为默认的根组件
	MyMesh->SetupAttachment(MyScene);
	MyParticle->SetupAttachment(MyScene);
	MyAudio->SetupAttachment(MyScene);
	MyBox->SetupAttachment(MyScene);

	//静态加载分为静态加载资源和静态加载类,静态加载必须在构造函数里
	//静态加载资源
	static ConstructorHelpers::FObjectFinder<UStaticMesh>TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe'"));
	MyMesh->SetStaticMesh(TempStaticMesh.Object);
	static ConstructorHelpers::FObjectFinder<UParticleSystem>TempParticle(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	MyParticle->SetTemplate(TempParticle.Object);
	static ConstructorHelpers::FObjectFinder<USoundWave>TempSoundWave(TEXT("/Script/Engine.SoundWave'/Game/StarterContent/Audio/Collapse01.Collapse01'"));
	MyAudio->SetSound(TempSoundWave.Object);

	////静态加载类,复制引用后，文件名后面必须加上"_C",不然会运行崩溃
	//static ConstructorHelpers::FClassFinder<AActor>TempMyActor(TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_WallSconce.Blueprint_WallSconce_C'"));
	//MyActor = TempMyActor.Class;//这样创建的只是在内容里，还要通过SpawnActor方法将它实例化到游戏里

	//碰撞设置
	//碰撞类型设置
	//MyBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MyBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//碰撞对象类型设置
	MyBox->SetCollisionObjectType(ECC_WorldDynamic);
	//碰撞响应
	MyBox->SetCollisionResponseToAllChannels(ECR_Overlap);//设置所有的通道
	//MyBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);//设置单个通道

	//设置Box的大小
	MyBox->SetBoxExtent(FVector(64, 64, 64));

#pragma endregion

}

// Called when the game starts or when spawned
void AMyActor1::BeginPlay()
{
	Super::BeginPlay();
	if (MyParticle)
	{
		//下面两个方法都可以
		//MyParticle->Deactivate();
		MyParticle->SetActive(false);
	}

#pragma region Dynamic

	//if (MyActor)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("My Actor is:%s"), *MyActor->GetName());
	//	AActor* TempSpawnActor = GetWorld()->SpawnActor<AActor>(MyActor, FVector(100, 500, 100), FRotator::ZeroRotator);
	//}
	////动态加载资源
	//UStaticMesh* TempStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	//if (TempStaticMesh)
	//{
	//	MyMesh->SetStaticMesh(TempStaticMesh);
	//}
	////动态加载类
	//UClass* TempClass = LoadClass<AActor>(this, TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight_C'"));
	//if (TempClass)
	//{
	//	AActor* SpawanActor = GetWorld()->SpawnActor<AActor>(TempClass, FVector::ZeroVector, FRotator::ZeroRotator);
	//	UE_LOG(LogTemp, Warning, TEXT("Class Name:"), *TempClass->GetName());
	//}

#pragma endregion

	//给碰撞添加处理函数
	MyBox->OnComponentBeginOverlap.AddDynamic(this, &AMyActor1::BeginOverlapFunc);
	MyBox->OnComponentEndOverlap.AddDynamic(this, &AMyActor1::EndOverlapFunc);
	MyBox->OnComponentHit.AddDynamic(this, &AMyActor1::HitFunc);
}

// Called every frame
void AMyActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//控制物体移动
	FVector tempOffset = FVector(1, 0, 0);
	FHitResult tempHitResult;
	//AddActorLocalOffset(tempOffset, false, &tempHitResult);//基于本地坐标的移动，会受到本身朝向的影响
	AddActorWorldOffset(tempOffset * speedMove, false, &tempHitResult);//基于世界坐标的移动，不会受到本身朝向的影响

}



void AMyActor1::BeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//先将其他碰撞到的转化成角色
	AMyCharacter1* tempCharacter = Cast<AMyCharacter1>(OtherActor);
	if (tempCharacter)
	{
		//应用伤害
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

