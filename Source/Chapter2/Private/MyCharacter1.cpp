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
	//将以下三个都设置为false是为了让控制器的转动不影响角色的转动，只影响摄像机的转动
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	//为了让角色面朝加速度的方向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//这个是使用pawan的旋转
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
			tempSubSys->AddMappingContext(MyMappingContext, 0);//第二个参数表示数值越大优先级越高

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

	//绑定映射，将玩家输入映射转化成增强输入映射
	UEnhancedInputComponent* tempEnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (tempEnhancedInputComponent)
	{
		//第一个参数是映射的变量，第二个是移动的方式,第三个是绑定的函数
		tempEnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &AMyCharacter1::Move);
		tempEnhancedInputComponent->BindAction(ActionRotate, ETriggerEvent::Triggered, this, &AMyCharacter1::Rotate);
	}
}

void AMyCharacter1::Move(const FInputActionValue& value)
{
	FVector2D tempMoveVec = value.Get<FVector2D>();
	//如果控制器有输入
	if (nullptr != Controller)
	{
		const FRotator tempRot = Controller->GetControlRotation();
		const FRotator	tempYaw(0, tempRot.Yaw, 0);
		const FVector	tempForwardDir = FRotationMatrix(tempYaw).GetUnitAxis(EAxis::X);//前方向的方向向量
		const FVector tempRightDir = FRotationMatrix(tempYaw).GetUnitAxis(EAxis::Y);//获得右方向的向量

		//添加键盘输入
		AddMovementInput(tempForwardDir, tempMoveVec.Y);//Y方向的移动
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

