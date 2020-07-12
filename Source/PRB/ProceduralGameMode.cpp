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
	GenerateSpawn();
}

//Disgusting code
void AProceduralGameMode::GenerateSpawn() {
	if (FLS_Cathedral.normalRooms.Num() > 0) {
		int numOptions = FLS_Cathedral.normalRooms.Num();
		int roomToPick = FMath::RandRange(0, numOptions - 1);
		currentRooms.Add(GetWorld()->SpawnActor<ARoomPrefab>(FLS_Cathedral.normalRooms[roomToPick]));
		if (currentRooms[0]) {
			for (int i = 0; i < currentRooms[0]->GetConnectorCount(); i++) {
				currentRooms.Add(GenerateAdjacent(FLS_Cathedral.normalRooms, currentRooms[0], i));
			}
		}
	}
}

ARoomPrefab* AProceduralGameMode::GenerateAdjacent(TArray<TSubclassOf<ARoomPrefab>> roomList, ARoomPrefab* baseRoom, int baseConnector) {
	URoomConnector* connector = baseRoom->GetConnector(baseConnector);
	if (connector) {
		TSubclassOf<ARoomPrefab> roomToSpawn = roomList[FMath::RandRange(0, roomList.Num() - 1)];
		ARoomPrefab* thisRoom = GetWorld()->SpawnActor<ARoomPrefab>(roomToSpawn);
		int connToPick = FMath::RandRange(0, thisRoom->GetConnectorCount() - 1);
		thisRoom->SetActorRotation((connector->GetForwardVector().Rotation() + FRotator(0, 180, 0)) - thisRoom->GetConnector(connToPick)->GetRelativeRotation());
		thisRoom->SetActorLocation(connector->GetComponentLocation() - thisRoom->GetConnector(connToPick)->GetComponentLocation());
		return thisRoom;
	}
	else {
		return NULL;
	}
}