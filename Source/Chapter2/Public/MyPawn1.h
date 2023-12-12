// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/DataTable.h"
#include "MyObject1.h"
#include "MyGameInstance1.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyPawn1.generated.h"

UENUM(BlueprintType)//生成枚举的反射数据，通过反射将枚举暴露给蓝图，实现C++和蓝图的通信,BlueprintType的作用是可以在蓝图创建变量的时候也可以作为选项
namespace MyEnumType
{
	enum MyCustomEnum2
	{
		Type1,
		Type2,
		Type3,
	};
}
UENUM(BlueprintType)
enum class MyCustomEnum1 :uint8
{
	OneType UMETA(DisplayName = "One"),
	TwoType UMETA(DisplayName = "Two"),
	ThreeType UMETA(DisplayName = "Three"),
};
USTRUCT(BlueprintType)
struct FDataStruct :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyDataStruct")
	int32 Age;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyDataStruct")
	FString MyName;
};

USTRUCT(BlueprintType)
struct FMyStruct//必须以F开头
{
	GENERATED_USTRUCT_BODY()
	FMyStruct();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")
	int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")
	FString MyName;
};

UCLASS()

class CHAPTER2_API AMyPawn1 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//这个注释也会被反射到面板上，当鼠标悬浮面板该变量时会显示当前注释
	//通过反射将属性暴露给蓝图的细节面板中，来实现C++和蓝图的通信
	UPROPERTY(VisibleDefaultsOnly)//VisibleDefaultsOnly表示仅在类默认设置可见
		int32 VisibleDefaultsOnlyInt;
	UPROPERTY(VisibleInstanceOnly)//仅仅在实例化细节面板可见
		FString VisibleInstanceString;
	UPROPERTY(VisibleAnywhere)//类默认设置和实例化细节面板都可见
		FVector VisibleAnywhereVector;
	//仅在类默认设置里面可以编辑
	UPROPERTY(EditDefaultsOnly)
	int32 EditDefaultsOnlyInt;
	//仅在实例化面板中可以编辑
	UPROPERTY(EditInstanceOnly)
	FString EditInstanceOnlyString;
	//在类默认设置和实例化细节面板都可以编辑
	UPROPERTY(EditAnywhere)
	FVector EditAnywhereVec;
	//在各个面板上可编辑，但是在蓝图中仅可读，
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 BlueprintReadOnlyInt;
	//在各个面板上可编辑，蓝图中可读可写
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString	BlueprintWriteReadString;

	//目录
	// 在蓝图中使用变量，将变量设置成目标目录
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyIntValue")
	int32 valueInt;
	//Meta元数据说明符
	//DisplayName别名，可以设置成中文
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "我是别名"))
	int32 myValue3;

	//条件可控制编辑,在面板上当控制变量为true时才可以对目标变量进行编辑
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "条件控制编辑变量"))
	bool isControl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "isControl"))
	float targetController;

	//解释说明变量,和注释类似，当有了这个后，注释部分会消失，只显示TooltTip的内容
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "当isControl=true时"))
	bool isTrue;

	/// <summary>
	/// 暴露该函数可在蓝图中调用
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void BlueprintCallable1();
	/// <summary>
	/// 可在蓝图中调用的纯函数的定义
	/// </summary>
	UFUNCTION(BlueprintPure, Category = "MyFunction")
	bool BlueprintPure2();
	/// <summary>
	/// 在C++中声明蓝图中实现，在蓝图中可重载,可以有参数和返回值，无返回值的是事件，有返回值的是函数
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
	void ImplementableEvent1();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	int32 ImplementableEvent2();
	UFUNCTION(BlueprintImplementableEvent)
	void ImplementableEvent3(const FString& myStr);
	UFUNCTION(BlueprintImplementableEvent)
	int32 ImplementableEvent4(const FString& myStr);

	/// <summary>
	/// 在C++中声明和实现，蓝图可重载，函数实现的后面要加Implementation，否则会编译出错,但是在调用的时候还是用声明时的名字。无返回值的是事件，有返回值的是函数
	/// </summary>
	UFUNCTION(BlueprintNativeEvent)
	void BlueprintNativeEvent1();
	UFUNCTION(BlueprintNativeEvent)
	int32 BlueprintNativeEvent2();
	UFUNCTION(BlueprintNativeEvent)
	void BlueprintNativeEvent3(const FString& myStr);
	UFUNCTION(BlueprintNativeEvent)
	int32 BlueprintNativeEvent4(const FString& myStr);

	//元数据说明符,也即别名，在蓝图中会显示DisplayName定义的名字
	UFUNCTION(BlueprintCallable, Category = "MyFunction", meta = (DisplayName = "MyPrintTest"))
	void PrintMeta();

	//枚举
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyEnum")
	TEnumAsByte<MyEnumType::MyCustomEnum2> MyCustomEnum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyEnum")
	MyCustomEnum1 MyEnum1;

	/// <summary>
	/// 生成蓝图时暴露的变量
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyExposeOnSpawn", meta = (ExposeOnSpawn))
	float myExposeOnSpawnValue;

	//结构体
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")
	FMyStruct MyStructValue;

	//实例化
	UMyObject1* MyTestObject;
	UMyGameInstance1* MyGameInstance;

public:

	//添加摄像机组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponent")
	USceneComponent* MyRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponent")
	USpringArmComponent* MySprintArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponent")
	UCameraComponent* MyCamera;

	//鼠标滑轮移动镜头缩放
	void ZoomCam(bool Dir, float ZoomSpeed);
};

