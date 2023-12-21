// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//����UI��ͷ�ļ�
#include "Components/WidgetComponent.h"
#include "MyInterface1.h"
//��ǿ����ͷ�ļ�
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
//���ͷ�ļ�
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "My3DWidget.h"
#include "TimerManager.h"//��ʱ��ͷ�ļ�
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
	/// ����������
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	class UInputMappingContext* MyMappingContext;
	/// <summary>
	/// һ���ƶ�������ӳ�����
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	class UInputAction* ActionMove;
	//��תӳ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	class UInputAction* ActionRotate;

	//������
	void Move(const	FInputActionValue& value);
	void Rotate(const FInputActionValue& value);

	//��ʱ������
	FTimerHandle Time;
	void PrintTime();

	//3DUI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My3DUI")
	UWidgetComponent* My3DUI;

	//�����߼��
	FVector startLocation;//��ʼλ��
	FVector forwardDir;//ǰ��������
	FVector	endLocation;
	FHitResult hitResult;//������ײ���ص�����

	//�����߼��
	TArray<FHitResult> listHitResult;

	//�첽���߼��Ļص�����
	FTraceDelegate traceDelegate;
	void AsynLlineTraceFunc(const FTraceHandle& handel, FTraceDatum& datum);

public:

	//��д�麯��
	virtual void Attack()override;
	virtual void CacluateHealth()override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;//��д���˺��������ڲ��Ѿ�ʵ����һ���߼�������ֻ����д��

};
