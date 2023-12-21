// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//加载UI的头文件
#include "Components/WidgetComponent.h"
#include "MyInterface1.h"
//增强输入头文件
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
//组件头文件
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "My3DWidget.h"
#include "TimerManager.h"//定时器头文件
#include "MyCharacter1.generated.h"

UCLASS()
class CHAPTER2_API AMyCharacter1 :public ACharacter, public IMyInterface1
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyComponent")
	USpringArmComponent* MySpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyComponent")
	UCameraComponent* MyCam;

	/// <summary>
	/// 输入上下文
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	class UInputMappingContext* MyMappingContext;
	/// <summary>
	/// 一个移动的输入映射变量
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	class UInputAction* ActionMove;
	//旋转映射
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	class UInputAction* ActionRotate;

	//函数绑定
	void Move(const	FInputActionValue& value);
	void Rotate(const FInputActionValue& value);

	//定时器变量
	FTimerHandle Time;
	void PrintTime();

	//3DUI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My3DUI")
	UWidgetComponent* My3DUI;

	//单射线检测
	FVector startLocation;//开始位置
	FVector forwardDir;//前向方向向量
	FVector	endLocation;
	FHitResult hitResult;//射线碰撞返回的数据

	//多射线检测
	TArray<FHitResult> listHitResult;

	//异步射线检测的回调函数
	FTraceDelegate traceDelegate;
	void AsynLlineTraceFunc(const FTraceHandle& handel, FTraceDatum& datum);

public:

	//重写虚函数
	virtual void Attack()override;
	virtual void CacluateHealth()override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;//重写下伤害函数，内部已经实现了一套逻辑，这里只需重写下

};
