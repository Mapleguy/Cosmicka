// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "WorldGen/LevelStruct.h"
#include "ProceduralGameMode.generated.h"

class ARoomPrefab;
class URoomConnector;

UCLASS()
class PRB_API AProceduralGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	AProceduralGameMode();

	UPROPERTY(EditAnywhere, Category = "Floor Data")
	FLevelScruct FLS_Cathedral;

	UPROPERTY(EditAnywhere, Category = "Floor Data")
	FLevelScruct currentFloor;

	UPROPERTY(VisibleAnywhere, Category = "Floors")
	TArray<ARoomPrefab*> currentRooms;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GenerateLevel();

	void GenerateSpawn();

	void GenerateBranch(URoomConnector* connector);

	ARoomPrefab* GenerateAdjacent(TArray<TSubclassOf<ARoomPrefab>> roomList, URoomConnector* connector);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};