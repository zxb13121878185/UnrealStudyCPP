// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter1.h"

// Sets default values
AMyCharacter1::AMyCharacter1()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
	MyCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCam"));

	MySpringArm->TargetArmLength = 400.0f;
	MyCam->SetupAttachment(MySpringArm);
	MySpringArm->SetupAttachment(RootComponent);
	//����������������Ϊfalse��Ϊ���ÿ�������ת����Ӱ���ɫ��ת����ֻӰ���������ת��
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	//Ϊ���ý�ɫ�泯���ٶȵķ���
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//�����ʹ��pawan����ת
	MySpringArm->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyCharacter1::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* tempPlayerCtr = Cast<APlayerController>(Controller);
	if (tempPlayerCtr)
	{
		UEnhancedInputLocalPlayerSubsystem* tempSubSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(tempPlayerCtr->GetLocalPlayer());
		if (tempSubSys)
		{
			tempSubSys->AddMappingContext(MyMappingContext, 0);//�ڶ���������ʾ��ֵԽ�����ȼ�Խ��

		}
	}
}

// Called every frame
void AMyCharacter1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//��ӳ�䣬���������ӳ��ת������ǿ����ӳ��
	UEnhancedInputComponent* tempEnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (tempEnhancedInputComponent)
	{
		//��һ��������ӳ��ı������ڶ������ƶ��ķ�ʽ,�������ǰ󶨵ĺ���
		tempEnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &AMyCharacter1::Move);
		tempEnhancedInputComponent->BindAction(ActionRotate, ETriggerEvent::Triggered, this, &AMyCharacter1::Rotate);
	}
}

void AMyCharacter1::Move(const FInputActionValue& value)
{
	FVector2D tempMoveVec = value.Get<FVector2D>();
	//���������������
	if (nullptr != Controller)
	{
		const FRotator tempRot = Controller->GetControlRotation();
		const FRotator	tempYaw(0, tempRot.Yaw, 0);
		const FVector	tempForwardDir = FRotationMatrix(tempYaw).GetUnitAxis(EAxis::X);//ǰ����ķ�������
		const FVector tempRightDir = FRotationMatrix(tempYaw).GetUnitAxis(EAxis::Y);//����ҷ��������

		//��Ӽ�������
		AddMovementInput(tempForwardDir, tempMoveVec.Y);//Y������ƶ�
		AddMovementInput(tempRightDir, tempMoveVec.X);
	}
}

void AMyCharacter1::Rotate(const FInputActionValue& value)
{
	FVector2D tempLookAxisVec = value.Get<FVector2D>();
	if (nullptr != Controller)
	{
		AddControllerYawInput(tempLookAxisVec.X);
		AddControllerPitchInput(tempLookAxisVec.Y);
	}

}

