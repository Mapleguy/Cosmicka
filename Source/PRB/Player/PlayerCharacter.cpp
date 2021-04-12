// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerCharacter.h"
#include "StatusComponent.h"
#include "../Weapons/PlayerWeapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../Interactables/InteractableActor.h"

#ifdef UE_BUILD_DEBUG 
#include "DrawDebugHelpers.h"
#endif

#define ECC_Interactable ECC_GameTraceChannel2

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup spring arm
	mainSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	if (mainSpringArm) {
		mainSpringArm->SetupAttachment(RootComponent);
		mainSpringArm->bUsePawnControlRotation = true;
	}

	//Setup main camera
	mainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	if (mainCamera) {
		mainCamera->SetupAttachment(mainSpringArm, USpringArmComponent::SocketName);
	}

	//Setup status component
	playerStatus = CreateDefaultSubobject<UStatusComponent>(TEXT("Player Status"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (WeaponToSpawn) {
		SpawnWeapon();
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::MovementJump);
	PlayerInputComponent->BindAction("PrimaryShoot", IE_Pressed, this, &APlayerCharacter::ShootPrimary);
	PlayerInputComponent->BindAction("PrimaryShoot", IE_Released, this, &APlayerCharacter::ShootPrimaryRelease);
	PlayerInputComponent->BindAction("SecondaryShoot", IE_Pressed, this, &APlayerCharacter::ShootSecondary);
	PlayerInputComponent->BindAction("SecondaryShoot", IE_Released, this, &APlayerCharacter::ShootSecondaryRelease);
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &APlayerCharacter::AttemptUse);

	PlayerInputComponent->BindAxis("Walk", this, &APlayerCharacter::MovementWalk);
	PlayerInputComponent->BindAxis("Strafe", this, &APlayerCharacter::MovementStrafe);
	PlayerInputComponent->BindAxis("LookX", this, &APlayerCharacter::CameraLookX);
	PlayerInputComponent->BindAxis("LookY", this, &APlayerCharacter::CameraLookY);
}

//Spawn the weapon and attach it to the camera
void APlayerCharacter::SpawnWeapon() {
	const FVector* offsetVector = new FVector(40, 20, -10);
	CurrentWeapon = GetWorld()->SpawnActor<APlayerWeapon>(WeaponToSpawn);
	CurrentWeapon->SetActorRelativeLocation(*offsetVector);
	FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, false);
	CurrentWeapon->AttachToComponent(mainCamera, rules);
}

/*----
Movement
----*/
//Walk
void APlayerCharacter::MovementWalk(float AxisValue) {
	FVector Direction = FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

//Strafe
void APlayerCharacter::MovementStrafe(float AxisValue) {
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

//Jump
void APlayerCharacter::MovementJump() {
	Jump();
}

/*----
Camera controls
----*/
void APlayerCharacter::CameraLookX(float AxisValue) {
	AddControllerYawInput(AxisValue);
}

void APlayerCharacter::CameraLookY(float AxisValue) {
	AddControllerPitchInput(AxisValue * -1);
}

/*----
Actions
----*/
void APlayerCharacter::ShootPrimary() {
	if (CurrentWeapon) {
		CurrentWeapon->PrimaryMouse(true);
	}
}

void APlayerCharacter::ShootPrimaryRelease() {
	if (CurrentWeapon) {
		CurrentWeapon->PrimaryMouse(false);
	}
}

void APlayerCharacter::ShootSecondary() {
	if (CurrentWeapon) {
		CurrentWeapon->SecondaryMouse(true);
	}
}

void APlayerCharacter::ShootSecondaryRelease() {
	if (CurrentWeapon) {
		CurrentWeapon->SecondaryMouse(false);
	}
}

void APlayerCharacter::AttemptUse() {
	//Begin raycast
	FHitResult hit;
	float rayLength = 500.0f;
	FVector rayOrigin = mainCamera->GetComponentLocation();
	FVector rayEndpoint = rayOrigin + (mainCamera->GetForwardVector() * rayLength);
	FCollisionQueryParams params;
	//params.bTraceComplex = true;
	GetWorld()->LineTraceSingleByChannel(hit, rayOrigin, rayEndpoint, ECC_Interactable, params);
	if (hit.IsValidBlockingHit()) {
		//GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Green, hit.Actor->GetClass());
		if (hit.Actor->GetClass()->IsChildOf(AInteractableActor::StaticClass())) {
			Cast<AInteractableActor>(hit.Actor)->Interact();
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Red, "This is NOT an interactable");
		}
	}
#ifdef UE_BUILD_DEBUG 
	DrawDebugLine(GetWorld(), rayOrigin, rayEndpoint, FColor::Red, false, 5.0f);
#endif
}