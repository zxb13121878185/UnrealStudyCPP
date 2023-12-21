// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Components/SphereComponent.h>
#include "Components/ArrowComponent.h"
#include "Actor_Bullet.generated.h"


UCLASS()
class CHAPTER2_API AActor_Bullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActor_Bullet();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "MyComponent")
	UStaticMeshComponent* BulletMesh;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "MyComponent")
	USphereComponent* Sphere;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "MyComponent")
	UProjectileMovementComponent* Projectile;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyComponent")
	UArrowComponent* Arrow;
};
