// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class PRB_API APlayerProjectile : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(Category = "Movement", EditAnywhere)
	UProjectileMovementComponent* projectileMovement;
public:	
	// Sets default values for this actor's properties
	APlayerProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitializeProjectile(FVector direction);
};
