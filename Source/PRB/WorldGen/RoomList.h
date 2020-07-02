#pragma once
#include "CoreMinimal.h"
#include "RoomPrefab.h"
#include "RoomList.generated.h"

USTRUCT(BlueprintType)
struct FRoomList{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Floor Data")
	int floorLevel;

	UPROPERTY(EditAnywhere, Category = "Rooms")
	TArray<TSubclassOf<ARoomPrefab>> roomList;
};