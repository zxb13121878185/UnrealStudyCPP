// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Bullet.h"

// Sets default values
AActor_Bullet::AActor_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	Bullet->SetStaticMesh(TempStaticMesh.Object);
	Bullet->SetRelativeScale3D(FVector(0.4,0.4,0.4));
	RootComponent = Bullet;
	Sphere->SetupAttachment(Bullet);
	Projectile->SetUpdatedComponent(Bullet);
	Projectile->InitialSpeed = 1200.0f;
	Projectile->MaxSpeed = 2400.0f;
	Projectile->bRotationFollowsVelocity = true;
	Projectile->bIsHomingProjectile = true;
	Projectile->ProjectileGravityScale = 1.5f;
}

// Called when the game starts or when spawned
void AActor_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActor_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

