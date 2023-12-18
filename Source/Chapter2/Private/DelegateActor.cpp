// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRawClass.h"
#include "DelegateActor.h"



// Sets default values
ADelegateActor::ADelegateActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//单播代理绑定
	//NoParamDelegate1.BindUObject(this, &ADelegateActor::NoParamDelegateFunc1);
	//NoParamDelegate1.Unbind();//解绑
	//NoParamDelegate1.BindStatic(StaticNoParamDelegate);//绑定全局静态函数
	//NoParamDelegate1.BindStatic(MyRawClass::RawStaticNoParamDelegateFunc);//绑定其他类的静态函数
	//MyRawClass tempRawClass;
	//NoParamDelegate1.BindRaw(&tempRawClass, &MyRawClass::Raw_NoParamDelegateFunc);//绑定其他类的成员函数

	////绑定一个Lambda表达式
	//auto LambdaDelegateFunc = []()->void
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("LambdaDelegateFunc")));
	//	};

	//NoParamDelegate1.BindLambda(LambdaDelegateFunc);
	//NoParamDelegate1.BindLambda(
	//	[]()->void
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("LambdaDelegateFunc")));
	//	}
	//);

	//OneParamDelegate1.BindUObject(this, &ADelegateActor::OneParamDelegateFunc);
	//TwoParamDelegate1.BindUObject(this, &ADelegateActor::TwoParamDelegateFunc);
	//OnlyRetDelegate1.BindUObject(this, &ADelegateActor::OnlyRetDelegateFunc);
	//RetOneParamDelegate1.BindUObject(this, &ADelegateActor::RetOneParamDelegateFunc);

	//多播代理的绑定
	//MulDelegate_OneParam1.AddUObject(this, &ADelegateActor::MulDelegate_OneParamFunc1);
	//MulDelegate_OneParam1.AddUObject(this, &ADelegateActor::MulDelegate_OneParamFunc2);
	//MulDelegate_OneParam.RemoveAll();

	//事件绑定
	//ActionEvent.AddUObject(this, &ADelegateActor::OneParamDelegateFunc);
}

// Called when the game starts or when spawned
void ADelegateActor::BeginPlay()
{
	Super::BeginPlay();

	//绑定智指针
	//TSharedRef<MyRawClass> ObjSP1 = MakeShareable(new MyRawClass());
	//NoParamDelegate1.BindSP(ObjSP1, &MyRawClass::Raw_NoParamDelegateFunc);

	//单播代理调用
	//NoParamDelegate1.ExecuteIfBound();
	//NoParamDelegate2.ExecuteIfBound();
	//OneParamDelegate1.ExecuteIfBound("TestStr");
	//TwoParamDelegate1.ExecuteIfBound("TwoParam", 22222);
	//OnlyRetDelegate1.Execute();//这个和上面的不一样
	//FString tempStr = RetOneParamDelegate1.Execute("this is:");
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, tempStr);

	////多播代理执行
	//MulDelegate_OneParam1.Broadcast("MulDelegate");

	////动态多播代理执行
	//DynamicMulDelegate.Broadcast("Dynamic Mul Cast");

	//事件触发
	//ActionEvent.Broadcast("Event Call");

}

// Called every frame
void ADelegateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADelegateActor::NoParamDelegateFunc1()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("NoParamDelegateFunc1")));
}

void ADelegateActor::NoParamDelegateFunc2()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("NoParamDelegateFunc2")));
}

void ADelegateActor::OneParamDelegateFunc(FString strVal)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("OneParamDelegateFunc:%s"), *strVal));
}

void ADelegateActor::TwoParamDelegateFunc(FString strVal, int32 intVal)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("NoParamDelegateFunc:%s,%d"), *strVal, intVal));
}
FString ADelegateActor::OnlyRetDelegateFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("OnlyRetDelegate")));
	return FString();
}

FString ADelegateActor::RetOneParamDelegateFunc(FString strVal)
{
	FString tempStr = strVal.Append("RetOneParamDelegateFunc");
	return FString(tempStr);
}

void ADelegateActor::MulDelegate_OneParamFunc1(FString strVal)
{
	FString tempStr = strVal.Append("1");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%s"), *tempStr));
}

void ADelegateActor::MulDelegate_OneParamFunc2(FString strVal)
{
	FString tempStr = strVal.Append("2");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%s"), *tempStr));
}



void StaticNoParamDelegate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("BindStatic")));
}
