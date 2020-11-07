// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomPrefab.generated.h"

class UArrowComponent;
class URoomConnector;

UENUM()
enum RoomType
{
	Standard UMETA(DisplayName = "Standard"),
	Spawn UMETA(DisplayName = "Spawn"),
	Boss UMETA(DisplayName = "Boss")
};

UCLASS()
class PRB_API ARoomPrefab : public AActor
{
	GENERATED_BODY()
private:
	//Base room mesh
	UPROPERTY(Category = "Room Data", EditAnywhere)
	UStaticMeshComponent* baseMesh;

	UPROPERTY(Category = "Room Data", EditAnywhere)
	int32 connCount;

	UPROPERTY(Category = "Room Data", EditAnywhere)
	TArray<URoomConnector*> connectionPoints;

public:	
	// Sets default values for this actor's properties
	ARoomPrefab();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//
	URoomConnector* GetConnectionPoint(int connector);

	//
	int GetConnectionCount();
};
