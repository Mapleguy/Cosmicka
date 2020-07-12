#pragma once
#include "CoreMinimal.h"
#include "RoomPrefab.h"
#include "LevelStruct.generated.h"

USTRUCT(BlueprintType)
struct FLevelScruct{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Floor")
	FString floorName;

	UPROPERTY(EditAnywhere, Category = "Floor")
	FString floorDescription;

	UPROPERTY(EditAnywhere, Category = "Floor", meta = (ClampMin = "1", ClampMax = "10"))
	int floorLevel;

	UPROPERTY(EditAnywhere, Category = "Floor", meta = (ClampMin = "6", ClampMax = "12"))
	int minRooms;

	UPROPERTY(EditAnywhere, Category = "Floor", meta = (ClampMin = "10", ClampMax = "50"))
	int maxRooms;

	UPROPERTY(EditAnywhere, Category = "Rooms | Spawn")
	TArray<TSubclassOf<ARoomPrefab>> spawnRooms;

	UPROPERTY(EditAnywhere, Category = "Rooms | Normal")
	TArray<TSubclassOf<ARoomPrefab>> normalRooms;

	UPROPERTY(EditAnywhere, Category = "Rooms | Special")
	TArray<TSubclassOf<ARoomPrefab>> specialRooms;

	UPROPERTY(EditAnywhere, Category = "Rooms | Boss")
	TArray<TSubclassOf<ARoomPrefab>> bossRooms;
};