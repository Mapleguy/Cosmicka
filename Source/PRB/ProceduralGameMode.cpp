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
			GenerateBranch(currentRooms[0]->GetTransform(), currentRooms[0]->GetConnectionPoint(i));
		}
	}

	if (currentRooms.Num() < currentFloor.maxRooms) {
		for (int i = 1; i < currentRooms.Num(); i++) {
			for (int j = 0; j < currentRooms[i]->GetConnectionCount(); j++) {
				GenerateBranch(currentRooms[i]->GetTransform(), currentRooms[i]->GetConnectionPoint(j));
			}
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

void AProceduralGameMode::GenerateBranch(FTransform roomOrigin, FTransform connector) {
	FTransform newConnector = connector;
	FTransform newOrigin = roomOrigin;
	while (currentRooms.Num() < currentFloor.maxRooms) {
		int spawnChance = FMath::RandRange(0, 10);
		if (spawnChance != 0) {
			ARoomPrefab* newRoom = GenerateAdjacent(currentFloor.normalRooms, newOrigin, newConnector);
			if (newRoom) {
				newConnector = newRoom->GetConnectionPoint(FMath::RandRange(0, newRoom->GetConnectionCount() - 1));
				newOrigin = newRoom->GetTransform();
			}
		}
		else {
			break;
		}
	}
}

/*Rotation now working, position is off when more than 1 room away from spawn*/
ARoomPrefab* AProceduralGameMode::GenerateAdjacent(TArray<TSubclassOf<ARoomPrefab>> roomList, FTransform roomOrigin, FTransform connector) {
	if (currentRooms.Num() < currentFloor.maxRooms) {
		TSubclassOf<ARoomPrefab> roomToSpawn = roomList[FMath::RandRange(0, roomList.Num() - 1)];

		int connToPick = FMath::RandRange(0, roomToSpawn->GetDefaultObject<ARoomPrefab>()->GetConnectionCount() - 1);
		FTransform newConnTransform = roomToSpawn->GetDefaultObject<ARoomPrefab>()->GetConnectionPoint(connToPick);

		FTransform spawnTransform;
		FRotator connectorRotation = roomOrigin.GetRotation().Rotator() + connector.GetRotation().Rotator() - FRotator(0, 180, 0);
		FRotator spawnRotation = (connectorRotation - newConnTransform.GetRotation().Rotator());

		float theta = FMath::UnwindRadians((spawnRotation.Yaw * 3.14159265) / 180);
		//FVector newPosition = FVector((newConnTransform.GetLocation().Y * FMath::Sin(theta) + newConnTransform.GetLocation().X * FMath::Cos(theta)), (newConnTransform.GetLocation().Y * FMath::Cos(theta) + newConnTransform.GetLocation().X * FMath::Sin(theta)), connector.GetLocation().Z);
		FVector newPosition = FVector((newConnTransform.GetLocation().Y * FMath::Sin(theta) + newConnTransform.GetLocation().X * FMath::Cos(theta)),
									  (newConnTransform.GetLocation().Y * FMath::Cos(theta) + newConnTransform.GetLocation().X * FMath::Sin(theta)),
			                           newConnTransform.GetLocation().Z);
		
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Yellow, newPosition.ToString());

		spawnTransform.SetRotation(spawnRotation.Quaternion());
		spawnTransform.SetLocation((roomOrigin.GetLocation() + connector.GetLocation()) - n ewPosition);

		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		ARoomPrefab* thisRoom = GetWorld()->SpawnActor<ARoomPrefab>(roomToSpawn, spawnTransform, params);

		if (thisRoom) {
			currentRooms.Add(thisRoom);
			return thisRoom;
		}
		else {
			return NULL;
		}
	}
	else {
		return NULL;
	}
}