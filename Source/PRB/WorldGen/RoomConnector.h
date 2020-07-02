// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RoomConnector.generated.h"

class UArrowComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRB_API URoomConnector : public USceneComponent
{
	GENERATED_BODY()
private: 
	//What type of room
	UPROPERTY(Category = "Connector Data", EditAnywhere)
	int connectorSize;

	UPROPERTY(Category = "Connector Data", EditAnywhere)
	UArrowComponent* arrow;

public:	
	// Sets default values for this component's properties
	URoomConnector();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};