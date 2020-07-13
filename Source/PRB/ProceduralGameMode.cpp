// Fill out your copyright notice in the Description page of Project Settings.
#include "ProceduralGameMode.h"
#include "WorldGen/RoomConnector.h"

AProceduralGameMode::AProceduralGameMode() {

}

void AProceduralGameMode::BeginPlay()
{
	Super::BeginPlay();

	GenerateLevel();
}

void AProceduralGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AProceduralGameMode::GenerateLevel() {
	currentFloor = FLS_Cathedral;
	GenerateSpawn();
	
	if (currentRooms[0]) {
		int numSpawnConns = currentRooms[0]->GetConnectionCount();
		for (int i = 0; i < numSpawnConns; i++) {
			GenerateBranch(currentRooms[0]->GetConnectionPoint(i));
		}
	}
}

//Disgusting code
void AProceduralGameMode::GenerateSpawn() {
	if (currentFloor.spawnRooms.Num() > 0) {
		int roomToPick = FMath::RandRange(0, currentFloor.spawnRooms.Num() - 1);
		currentRooms.Add(GetWorld()->SpawnActor<ARoomPrefab>(currentFloor.spawnRooms[roomToPick]));
	}
}

void AProceduralGameMode::GenerateBranch(FTransform connector) {
	FTransform newConnector = connector;
	while (currentRooms.Num() < currentFloor.maxRooms) {
		int spawnChance = FMath::RandRange(0, 8);
		if (spawnChance != 0) {
			ARoomPrefab* newRoom = GenerateAdjacent(currentFloor.normalRooms, newConnector);
			if (newRoom) {
				newConnector = newRoom->GetConnectionPoint(FMath::RandRange(0, newRoom->GetConnectionCount() - 1));
			}
		}
		else {
			break;
		}
	}
}

ARoomPrefab* AProceduralGameMode::GenerateAdjacent(TArray<TSubclassOf<ARoomPrefab>> roomList, FTransform connector) {
	TSubclassOf<ARoomPrefab> roomToSpawn = roomList[FMath::RandRange(0, roomList.Num() - 1)];

	int connToPick = FMath::RandRange(0, roomToSpawn->GetDefaultObject<ARoomPrefab>()->GetConnectionCount() - 1);
	FTransform connTransform = roomToSpawn->GetDefaultObject<ARoomPrefab>()->GetConnectionPoint(connToPick);

	FTransform spawnTransform;
	FRotator spawnRotation = ((connector.GetRotation().Rotator() + FRotator(0, 180, 0)) - connTransform.GetRotation().Rotator());
	spawnTransform.SetRotation(spawnRotation.Quaternion());

	FRotator diff = connTransform.GetRotation().Rotator() - (connector.GetRotation().Rotator() - FRotator(0, 180, 0));
	float theta = (diff.Yaw * 3.14159) / 180;
	FVector newPosition = FVector((connTransform.GetLocation().Y * FMath::Sin(theta) + connTransform.GetLocation().X * FMath::Cos(theta)), (connTransform.GetLocation().Y * FMath::Cos(theta) + connTransform.GetLocation().X * FMath::Sin(theta)), connector.GetLocation().Z);
	spawnTransform.SetLocation(connector.GetLocation() - newPosition);
	/*GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, FString::SanitizeFloat(theta));
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Blue, connTransform.GetLocation().ToString());
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, newPosition.ToString());*/

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	ARoomPrefab* thisRoom = GetWorld()->SpawnActor<ARoomPrefab>(roomToSpawn, spawnTransform, params);
	if (thisRoom) {
		//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, "Could Spawn Room");
		currentRooms.Add(thisRoom);
		return thisRoom;
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, "Could Not Spawn Room");
		return NULL;
	}
}