// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WorldGen/RoomList.h"
#include "ProceduralGameMode.generated.h"

class ARoomPrefab;

UCLASS()
class PRB_API AProceduralGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	AProceduralGameMode();

	UPROPERTY(EditAnywhere, Category = "Floors|Floor 1")
	TArray<TSubclassOf<ARoomPrefab>> F1_Spawns;

	UPROPERTY(EditAnywhere, Category = "Floors|Floor 1")
	TArray<TSubclassOf<ARoomPrefab>> F1_Standards;

	UPROPERTY(EditAnywhere, Category = "Floors|Floor 1")
	TArray<TSubclassOf<ARoomPrefab>> F1_Bosses;

	UPROPERTY(VisibleAnywhere, Category = "Floors")
	TArray<ARoomPrefab*> currentRooms;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GenerateLevel();

	void GenerateSpawn();

	void GenerateAdjacent();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};