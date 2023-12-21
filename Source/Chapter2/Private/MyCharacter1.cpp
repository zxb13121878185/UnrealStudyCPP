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

	//ÿ���̶����ӡ,������������ֱ�Ϊ����¼����Ƿ�ѭ��
	GetWorld()->GetTimerManager().SetTimer(Time, this, &AMyCharacter1::PrintTime, 1.0f, true);

	////���ʱ��
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

	//ʹ�����߼��
	forwardDir = MyCam->GetForwardVector();
	startLocation = MyCam->GetComponentLocation();
	endLocation = startLocation + forwardDir * 9999;


	FCollisionObjectQueryParams tempObjectType;
	tempObjectType.AddObjectTypesToQuery(ECC_WorldDynamic);
	FCollisionQueryParams tempQueryParams;
	tempQueryParams.AddIgnoredActor(this->GetUniqueID());
	//bool bTempHit;
	////����ͨ�����м��
	// bTempHit = GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECC_Visibility);//���һ��Ϊͨ�����ͣ�����ͨ�����м��
	//����Ŀ���������ͽ��м��
	//	tempObjectType.AddObjectTypesToQuery(ECC_WorldStatic);
	 //bTempHit = GetWorld()->LineTraceSingleByObjectType(hitResult, startLocation, endLocation, tempObjectType);
	//CPPTestΪ�½�����ײԤ��
	// bTempHit = GetWorld()->LineTraceSingleByProfile(hitResult, startLocation, endLocation, "CPPTest");
	//bTempHit = GetWorld()->LineTraceTestByChannel(startLocation, endLocation, ECC_WorldDynamic);

	/////������״�����߼��
	//FCollisionShape tempBoxShape = FCollisionShape::MakeBox(FVector(10, 100, 10));
	//FQuat tempRot = FQuat::MakeFromEuler(FVector(0, 0, 0));
	//bTempHit = GetWorld()->SweepSingleByChannel(hitResult, startLocation, endLocation, tempRot, ECC_WorldDynamic, tempBoxShape);
	//GetWorld()->bDebugDrawAllTraceTags = true;

	//�첽����
	traceDelegate.BindUObject(this, &AMyCharacter1::AsynLlineTraceFunc);
	const FCollisionResponseParams tempResponsParam = FCollisionResponseParams::DefaultResponseParam;
	GetWorld()->AsyncLineTraceByChannel(EAsyncTraceType::Multi, startLocation, endLocation, ECC_WorldDynamic, tempQueryParams, tempResponsParam, &traceDelegate);

	////�����߼��ͨ�����
	//bool bTempHit3 = GetWorld()->LineTraceMultiByChannel(listHitResult, startLocation, endLocation, ECC_Visibility);

	//////�����߶�����
	//tempObjectType.AddObjectTypesToQuery(ECC_Visibility);
	//bool bTempHit4 = GetWorld()->LineTraceMultiByObjectType(listHitResult, startLocation, endLocation, tempObjectType);
	// 
	// 

	//if (bTempHit)
	//{
	//	AActor* tempHitActor = hitResult.GetActor();
	//	FVector tempImpactPoint = hitResult.ImpactPoint;//���߻��еĵ�
	//	FVector tempHitLocation = hitResult.Location;//���е��λ��
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

