// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerWeapon.h"
#include "PlayerProjectile.h"
#include "WeaponProjectileSpawn.h"

// Sets default values
APlayerWeapon::APlayerWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create projectile spawn
	rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	if (rootComponent) {
		SetRootComponent(rootComponent);
	}
	projectileSpawn = CreateDefaultSubobject<UWeaponProjectileSpawn>(TEXT("Projectile Spawn Point"));
	if (projectileSpawn) {
		projectileSpawn->SetupAttachment(RootComponent);
	}

}

// Called when the game starts or when spawned
void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (rootComponent) {
		rootComponent->SetRelativeLocation(FVector(30, 0, 0));
	}
}

// Called every frame
void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerWeapon::PrimaryMouse(bool pressed) {
	primaryMouseDown = pressed;
	SetFireTimer();
}

void APlayerWeapon::SecondaryMouse(bool pressed) {
	secondaryMouseDown = pressed;
	SetFireTimer();
}

//Set firing timer
void APlayerWeapon::SetFireTimer() {
	//Set fire rate
	float firerate = 0;
	if (baseFireRate * multFireRate <= 0.0f) {
		firerate = 1.0f;
	}
	else {
		firerate = 1 / (baseFireRate * multFireRate);
	}
	switch (weaponType)
	{
	case WeaponType::Launcher:
		if (!GetWorldTimerManager().IsTimerActive(handle)) {
			GetWorldTimerManager().SetTimer(handle, this, &APlayerWeapon::FireLauncher, firerate, true, 0.0f);
		}
		break;
	case WeaponType::Semi:
		if (!GetWorldTimerManager().IsTimerActive(handle)) {
			GetWorldTimerManager().SetTimer(handle, this, &APlayerWeapon::FireSemi, firerate, false, 0.0f);
		}
		break;
	case WeaponType::Auto:
		if (!GetWorldTimerManager().IsTimerActive(handle)) {
			GetWorldTimerManager().SetTimer(handle, this, &APlayerWeapon::FireAuto, firerate, true, 0.0f);
		}
		break;
	case WeaponType::Custom:
		FireCustom();
		break;
	}
}

//Firing
void APlayerWeapon::FireLauncher() {
	if (primaryMouseDown) {
		FActorSpawnParameters params;
		APlayerProjectile* projectile = GetWorld()->SpawnActor<APlayerProjectile>(weaponProjectile, projectileSpawn->GetComponentTransform(), params);
		if (projectile) {
			projectile->InitializeProjectile(projectileSpawn->GetForwardVector() * 1000);
		}
	}
	else {
		GetWorldTimerManager().ClearTimer(handle);
	}
}

void APlayerWeapon::FireSemi() {
	if (primaryMouseDown) {

	}
	else {
		GetWorldTimerManager().ClearTimer(handle);
	}
}

void APlayerWeapon::FireAuto() {
	if (primaryMouseDown) {

	}
	else {
		GetWorldTimerManager().ClearTimer(handle);
	}
}