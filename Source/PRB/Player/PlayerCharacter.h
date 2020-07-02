// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class APlayerWeapon;
class USpringArmComponent;
class UCameraComponent;
class UStatusComponent;

UCLASS()
class PRB_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category="Weapon", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APlayerWeapon> WeaponToSpawn;

	UPROPERTY(Category = "Weapon", VisibleAnywhere)
	APlayerWeapon* CurrentWeapon;

	UPROPERTY(Category = "Camera", VisibleAnywhere)
	USpringArmComponent* mainSpringArm;
	UPROPERTY(Category = "Camera", VisibleAnywhere)
	UCameraComponent* mainCamera;

	UPROPERTY(Category = "Player Status", VisibleAnywhere)
	UStatusComponent* playerStatus;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Spawn weapon
	void SpawnWeapon();

	//Attempt to use item when 'use' button is pressed
	void AttemptUse();

	//Walk
	void MovementWalk(float AxisValue);
	//Strafe
	void MovementStrafe(float AxisValue);
	//Jump
	void MovementJump();
	//Look X
	void CameraLookX(float AxisValue);
	//Look Y
	void CameraLookY(float AxisValue);

	//Shoot primary
	void ShootPrimary();
	void ShootPrimaryRelease();
	//Shoot secondary
	void ShootSecondary();
	void ShootSecondaryRelease();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};