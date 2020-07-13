// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WorldGen/LevelStruct.h"
#include "ProceduralGameMode.generated.h"

class ARoomPrefab;

UCLASS()
class PRB_API AProceduralGameMode : public AGameModeBase
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

	void GenerateBranch(FTransform connector);

	ARoomPrefab* GenerateAdjacent(TArray<TSubclassOf<ARoomPrefab>> roomList, FTransform connector);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};