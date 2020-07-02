// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRB_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

	//Default values
	UPROPERTY(EditAnywhere, Category = "Default Values")
	int defaultHealth;
	UPROPERTY(EditAnywhere, Category = "Default Values")
	int defaultArmor;
	UPROPERTY(EditAnywhere, Category = "Default Values")
	float defaultDamageBase;
	UPROPERTY(EditAnywhere, Category = "Default Values")
	float defaultDamageMultiplier;
	UPROPERTY(EditAnywhere, Category = "Default Values")
	float defaultSpeedBase;
	UPROPERTY(EditAnywhere, Category = "Default Values")
	float defaultSpeedMultiplier;
	UPROPERTY(EditAnywhere, Category = "Default Values")
	int defaultJumpCount;
	UPROPERTY(EditAnywhere, Category = "Default Values")
	float defaultJumpHeight;
	UPROPERTY(EditAnywhere, Category = "Default Values")
	float defaultJumpSpeed;

	//Health
	UPROPERTY(EditAnywhere, Category = "Health")
	int maxHealth;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int currentHealth;
	//Armor
	UPROPERTY(EditAnywhere, Category = "Health")
	int maxArmor;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int currentArmor;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
