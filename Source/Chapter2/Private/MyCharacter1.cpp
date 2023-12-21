// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter1.h"

// Sets default values
AMyCharacter1::AMyCharacter1()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
	MyCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCam"));

	My3DUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("My3DUI"));
	My3DUI->SetupAttachment(RootComponent);
	static ConstructorHelpers::FClassFinder<UUserWidget>tempUICalss(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI3D.UI3D_C'"));
	My3DUI->SetWidgetClass(tempUICalss.Class);
	My3DUI->SetRelativeLocation(FVector(0, 0, 100));
	My3DUI->SetWidgetSpace(EWidgetSpace::World);
	My3DUI->SetDrawSize(FVector2D(400, 20));

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

	//每个固定秒打印,最后两个参数分别为间隔事件和是否循环
	GetWorld()->GetTimerManager().SetTimer(Time, this, &AMyCharacter1::PrintTime, 1.0f, true);

	////清除时间
	if (Time.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(Time);
	}
}

// Called every frame
void AMyCharacter1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#pragma region LineTrace

	//使用射线检测
	forwardDir = MyCam->GetForwardVector();
	startLocation = MyCam->GetComponentLocation();
	endLocation = startLocation + forwardDir * 9999;


	FCollisionObjectQueryParams tempObjectType;
	tempObjectType.AddObjectTypesToQuery(ECC_WorldDynamic);
	FCollisionQueryParams tempQueryParams;
	tempQueryParams.AddIgnoredActor(this->GetUniqueID());
	//bool bTempHit;
	////根据通道进行检测
	// bTempHit = GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECC_Visibility);//最后一个为通道类型，根据通道进行检测
	//根据目标物体类型进行检测
	//	tempObjectType.AddObjectTypesToQuery(ECC_WorldStatic);
	 //bTempHit = GetWorld()->LineTraceSingleByObjectType(hitResult, startLocation, endLocation, tempObjectType);
	//CPPTest为新建的碰撞预设
	// bTempHit = GetWorld()->LineTraceSingleByProfile(hitResult, startLocation, endLocation, "CPPTest");
	//bTempHit = GetWorld()->LineTraceTestByChannel(startLocation, endLocation, ECC_WorldDynamic);

	/////其他形状的射线检测
	//FCollisionShape tempBoxShape = FCollisionShape::MakeBox(FVector(10, 100, 10));
	//FQuat tempRot = FQuat::MakeFromEuler(FVector(0, 0, 0));
	//bTempHit = GetWorld()->SweepSingleByChannel(hitResult, startLocation, endLocation, tempRot, ECC_WorldDynamic, tempBoxShape);
	//GetWorld()->bDebugDrawAllTraceTags = true;

	//异步处理
	traceDelegate.BindUObject(this, &AMyCharacter1::AsynLlineTraceFunc);
	const FCollisionResponseParams tempResponsParam = FCollisionResponseParams::DefaultResponseParam;
	GetWorld()->AsyncLineTraceByChannel(EAsyncTraceType::Multi, startLocation, endLocation, ECC_WorldDynamic, tempQueryParams, tempResponsParam, &traceDelegate);

	////多射线检测通道检测
	//bool bTempHit3 = GetWorld()->LineTraceMultiByChannel(listHitResult, startLocation, endLocation, ECC_Visibility);

	//////多射线对象检测
	//tempObjectType.AddObjectTypesToQuery(ECC_Visibility);
	//bool bTempHit4 = GetWorld()->LineTraceMultiByObjectType(listHitResult, startLocation, endLocation, tempObjectType);
	// 
	// 

	//if (bTempHit)
	//{
	//	AActor* tempHitActor = hitResult.GetActor();
	//	FVector tempImpactPoint = hitResult.ImpactPoint;//射线击中的点
	//	FVector tempHitLocation = hitResult.Location;//击中点的位置
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Yellow, FString::Printf(TEXT("hit name:%s"), *tempHitActor->GetName()));
	//}
	//if (bTempHit4)
	//{
	//	for (int i = 0; i < listHitResult.Num(); i++)
	//	{
	//		AActor* tempHitActor = listHitResult[i].GetActor();
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("hit name:%s"), *tempHitActor->GetName()));
	//	}
	//}


#pragma endregion


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

void AMyCharacter1::PrintTime()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Time"));
}

void AMyCharacter1::AsynLlineTraceFunc(const FTraceHandle& handel, FTraceDatum& datum)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("AsynLlineTraceFunc:%d"), datum.OutHits.Num()));
	for (int32 i = 0; i < datum.OutHits.Num(); i++)
	{
		AActor* tempHitActor = datum.OutHits[i].GetActor();
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("hit name:%s"), *tempHitActor->GetName()));
	}
}

void AMyCharacter1::Attack()
{

}

void AMyCharacter1::CacluateHealth()
{

}

float AMyCharacter1::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	UMy3DWidget* temp3DUI = Cast<UMy3DWidget>(My3DUI->GetUserWidgetObject());
	if (temp3DUI)
	{
		if (temp3DUI->CurHealth > 0)
		{
			temp3DUI->CurHealth -= 5.0f;
		}
		return 0;
	}
	return 0.0f;
}

