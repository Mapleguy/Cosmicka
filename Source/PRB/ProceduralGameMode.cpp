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

//Digusting code
void AProceduralGameMode::GenerateSpawn() {
	if (F1_Spawns.Num() > 0) {
		int numOptions = F1_Spawns.Num();
		int roomToPick = FMath::RandRange(0, numOptions - 1);
		currentRooms.Add(GetWorld()->SpawnActor<ARoomPrefab>(F1_Spawns[roomToPick]));
		if (currentRooms[0]) {
			for (int i = 0; i < currentRooms[0]->GetConnectorCount(); i++) {
				URoomConnector* connector = currentRooms[0]->GetConnector(i);
				if (connector) {
					int numOptions2 = F1_Spawns.Num();
					int roomToPick2 = FMath::RandRange(0, numOptions2 - 1);
					TSubclassOf<ARoomPrefab> roomToSpawn = F1_Spawns[roomToPick2];
					ARoomPrefab* thisRoom = GetWorld()->SpawnActor<ARoomPrefab>(roomToSpawn);
					thisRoom->SetActorRotation((connector->GetForwardVector().Rotation() + FRotator(0, 180, 0)) - thisRoom->GetConnector(0)->GetRelativeRotation());
					thisRoom->SetActorLocation(connector->GetComponentLocation() - thisRoom->GetConnector(0)->GetComponentLocation());
					currentRooms.Add(thisRoom);
				}
			}
		}
	}
}