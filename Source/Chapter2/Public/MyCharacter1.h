// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter1.generated.h"

UCLASS()
class CHAPTER2_API AMyCharacter1 : public ACharacter
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
};
