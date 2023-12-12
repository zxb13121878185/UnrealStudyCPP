// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn1.h"
#include "MyObject1.h"
#include "MyActor1.h"

// Sets default values
AMyPawn1::AMyPawn1()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	MySprintArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCam"));
	RootComponent = MyRoot;
	MySprintArm->SetupAttachment(MyRoot);
	MyCamera->SetupAttachment(MySprintArm);
	MySprintArm->bDoCollisionTest = false;//碰撞检测关闭
}

// Called when the game starts or when spawned
void AMyPawn1::BeginPlay()
{
	Super::BeginPlay();
	//BlueprintNativeEvent1_Implementation();//如果用这个调用会执行C++的代码，不会执行蓝图中的功能
	//BlueprintNativeEvent1();//使用这个声明而不是上述带后缀_Implementation的方法可以实现蓝图被调用，而C++中的不会被调用

	//ImplementableEvent1();
	//ImplementableEvent2();

#pragma region MyRegion

	//实例化一个Object类
	//TSubclassOf<UMyObject1> MySubclassObject = UMyObject1::StaticClass();
	//MyTestObject = NewObject<UMyObject1>(GetWorld(), MySubclassObject);
	//if (MyTestObject)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("This is a %s"), *MyTestObject->GetName());
	//	UE_LOG(LogTemp, Warning, TEXT("Age:%d ,Name:%s"), MyTestObject->MyData.Age, *MyTestObject->MyData.MyName);
	//}

	//实例化一个Actor类
	//TSubclassOf<AMyActor1> MySubclassObject = AMyActor1::StaticClass();
	//AMyActor1* TempActor = NewObject<AMyActor1>(GetWorld(), MySubclassObject);
	//if (TempActor)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("This is a %s"), *TempActor->GetName());
	//}

	////赋值一个Game Instance
	//MyGameInstance = Cast<UMyGameInstance1>(GetWorld()->GetFirstPlayerController()->GetGameInstance());
	//if (MyGameInstance)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("My Instance Name:%s,IP:%d, UserName:%s"), *MyGameInstance->GetName(), MyGameInstance->IP, *MyGameInstance->UserName);
	//}

#pragma endregion

	//摄像机摇臂设置其旋转位移和缩放
	FVector	tempLocation = FVector(0, 0, 0);
	FRotator tempRot = FRotator(-50, 0, 0);
	FVector tempScale = FVector(1, 1, 1);
	SetActorLocation(tempLocation);
	SetActorRotation(tempRot);
	SetActorScale3D(tempScale);

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

FMyStruct::FMyStruct()
{
	MyName = TEXT("Default");
	Health = 0;
}
