// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Bullet.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AActor_Bullet::AActor_Bullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	BulletMesh->SetStaticMesh(TempStaticMesh.Object);
	BulletMesh->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));

	//RootComponent = BulletMesh;

	BulletMesh->SetupAttachment(RootComponent);
	Arrow->SetupAttachment(RootComponent);
	Sphere->SetupAttachment(RootComponent);
	Projectile->SetUpdatedComponent(RootComponent);
	Projectile->InitialSpeed = 1200.0f;
	Projectile->MaxSpeed = 2400.0f;
	Projectile->bRotationFollowsVelocity = true;
	Projectile->bIsHomingProjectile = true;
	Projectile->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void AActor_Bullet::BeginPlay()
{
	Super::BeginPlay();

	//改变物体材质的属性

	UMaterialInstanceDynamic* tempMat = BulletMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (tempMat)
	{
		tempMat->SetVectorParameterValue("Color", FLinearColor::Yellow);
	}
}

// Called every frame
void AActor_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

