// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Elevator.generated.h"

/**
 * 
 */
UCLASS()
class PRB_API AElevator : public AInteractableActor
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "Elevator", EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* interactMesh;
	UPROPERTY(Category = "Elevator", EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* platformMesh;

public:
	// Sets default values for this actor's properties
	AElevator();

	virtual void Interact() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Elevator")
	void ToggleElevator();
	virtual void ToggleElevator_Implementation();
};
