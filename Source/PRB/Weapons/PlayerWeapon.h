// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerWeapon.generated.h"

class APlayerProjectile;
class UWeaponProjectileSpawn;

UENUM()
enum WeaponType
{
	Launcher UMETA(DisplayName = "Launcher"),
	Semi UMETA(DisplayName = "Semi-automatic"),
	Auto UMETA(DisplayName = "Automatic"),
	Custom UMETA(DisplayName = "Custom")
};

UCLASS()
class PRB_API APlayerWeapon : public AActor
{
	GENERATED_BODY()
protected:
	//Weapon type
	UPROPERTY(Category = "Weapon Data", EditAnywhere)
	TEnumAsByte<WeaponType> weaponType;

	//Projectile
	UPROPERTY(Category = "Weapon Data", EditAnywhere)
	TSubclassOf<APlayerProjectile> weaponProjectile;

	//Projectile spawn point
	UPROPERTY(Category = "Weapon Data", EditAnywhere)
	UWeaponProjectileSpawn* projectileSpawn;

	//Weapon empty scene component
	USceneComponent* rootComponent;

	//Weapon Stats
	//Base fire rate in shots/second
	UPROPERTY(Category = "Weapon Data|Stats", EditAnywhere)
	int baseFireRate;

	//Fire rate multiplier
	UPROPERTY(Category = "Weapon Data|Stats", EditAnywhere)
	float multFireRate;

	//Fire projectile count for weapons like shotguns
	UPROPERTY(Category = "Weapon Data|Stats", EditAnywhere)
	int projectileCount;

	//If mouse is pressed down
	bool primaryMouseDown;
	bool secondaryMouseDown;

	FTimerHandle handle;

public:	
	// Sets default values for this actor's properties
	APlayerWeapon();

	//Tell the weapon if the primary mouse button is down or not
	void PrimaryMouse(bool pressed);

	//Tell the weapon if the secondary button is down or not
	void SecondaryMouse(bool pressed);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*----
	Firing modes
	-FireLauncher is automatic and launches a physical projectile of some sort
	-FireSemi is semiautomatic hitscan and fire when pressed
	-FireAuto is automatic and fires as long as the mouse is down
	-FireCustom is a virtual function that can be overrides for special guns
	----*/
	void FireLauncher();
	void FireSemi();
	void FireAuto();
	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void FireCustom();

	//Set timer for firing weapons
	void SetFireTimer();
	//Fire weapon, not used to actually fire weapon


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
