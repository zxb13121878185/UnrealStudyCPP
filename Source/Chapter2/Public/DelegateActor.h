// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyRawClass.h"
#include "GameFramework/Actor.h"
#include "DelegateActor.generated.h"

//单播委托类的声明
DECLARE_DELEGATE(NoParamDelegate);//没有参数没有返回值的委托，委托名称为“NoParamDelegate”
DECLARE_DELEGATE_OneParam(OneParamDelegate, FString);//一个参数没有返回值的委托，名称为“OneParamDelegate”
DECLARE_DELEGATE_TwoParams(TwoParamDelegate, FString, int32);//两个参数没有返回值的委托，名称为“TwoParamDelegate”
DECLARE_DELEGATE_RetVal(FString, OnlyRetDelegate);//仅仅是返回值的委托，名称为“OnlyRetDelegate”
DECLARE_DELEGATE_RetVal_OneParam(FString, RetOneParamDelegate, FString);//定义了带参数和返回值的委托，第一个参数为返回值，第二个为委托名称，第三个为返回值

//多播委托类声明
DECLARE_MULTICAST_DELEGATE_OneParam(MulDelegate_OneParam, FString);//带一个参数的

//事件声明
DECLARE_EVENT_OneParam(MyRawClass, MyActionEvent1, FString);

//动态多播委托，区别在于它可以暴露给蓝图，在蓝图中进行事件的绑定
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynamicMulDelegate, FString, param);//一个参数的动态多播委托,名称一定要F开头不然会编译报错“Delegate type declarations must start with F”




static void StaticNoParamDelegate();

UCLASS()
class CHAPTER2_API ADelegateActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADelegateActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//单播代理变量的声明
	NoParamDelegate NoParamDelegate1;
	NoParamDelegate NoParamDelegate2;
	OneParamDelegate OneParamDelegate1;
	TwoParamDelegate TwoParamDelegate1;
	OnlyRetDelegate OnlyRetDelegate1;
	RetOneParamDelegate RetOneParamDelegate1;
	//多播代理声明
	MulDelegate_OneParam MulDelegate_OneParam1;
	//动态多播代理变量声明
	UPROPERTY(BlueprintAssignable)//可以让代理在蓝图中进行绑定
		FDynamicMulDelegate DynamicMulDelegate;

	//单播代理绑定函数定义
	void NoParamDelegateFunc1();
	void NoParamDelegateFunc2();
	void OneParamDelegateFunc(FString strVal);
	void TwoParamDelegateFunc(FString strVal, int32 intVal);
	FString OnlyRetDelegateFunc();
	FString RetOneParamDelegateFunc(FString strVal);

	//多播委托绑定函数定义
	void MulDelegate_OneParamFunc1(FString strVal);
	void MulDelegate_OneParamFunc2(FString strVal);

	//动态多播委托在蓝图或其他执行中完成动态绑定，无需在此定义绑定函数

	//事件变量
	MyActionEvent1 ActionEvent;
};
