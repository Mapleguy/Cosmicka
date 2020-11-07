// Fill out your copyright notice in the Description page of Project Settings.
#include "ProceduralGameMode.h"
#include "WorldGen/RoomConnector.h"
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

	if (currentRooms.Num() < currentFloor.maxRooms) {
		for (int i = 1; i < currentRooms.Num(); i++) {
			for (int j = 0; j < currentRooms[i]->GetConnectionCount(); j++) {
				GenerateBranch(currentRooms[i]->GetConnectionPoint(j));
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

void AProceduralGameMode::GenerateBranch(URoomConnector* connector) {
	while (currentRooms.Num() < 2 /*currentFloor.maxRooms*/) {
		URoomConnector* newConnector = connector;
		int spawnChance = FMath::RandRange(0, 10);
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

/*Rotation now working, position is off when more than 1 room away from spawn*/
ARoomPrefab* AProceduralGameMode::GenerateAdjacent(TArray<TSubclassOf<ARoomPrefab>> roomList, URoomConnector* connector) {
	if (currentRooms.Num() < currentFloor.maxRooms) {
		TSubclassOf<ARoomPrefab> roomToSpawn = roomList[FMath::RandRange(0, roomList.Num() - 1)];

		int connToPick = FMath::RandRange(0, roomToSpawn->GetDefaultObject<ARoomPrefab>()->GetConnectionCount() - 1);
		URoomConnector* newConnector = roomToSpawn->GetDefaultObject<ARoomPrefab>()->GetConnectionPoint(connToPick);
		if (!newConnector) {
			GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, "FUCK");
			return nullptr;
		}

		FTransform spawnTransform;
		FRotator connectorRotation = connector->GetComponentToWorld().Rotator();
		FRotator spawnRotation = (connectorRotation - newConnector->GetRelativeRotation());

		float theta = FMath::UnwindRadians((spawnRotation.Yaw * 3.14159) / 180);

		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Yellow, FString::SanitizeFloat(theta));

		//FVector newPosition = connector.GetScaledAxis(EAxis::X) * newConnector.GetLocation().Size();

		/*FVector newPosition = FVector((newConnTransform.GetLocation().Y * FMath::Sin(theta) + newConnTransform.GetLocation().X * FMath::Cos(theta)),
									  (newConnTransform.GetLocation().Y * FMath::Cos(theta) + newConnTransform.GetLocation().X * FMath::Sin(theta)),
			                           newConnTransform.GetLocation().Z);

		FVector connPosition = FVector((connector.GetLocation().X * FMath::Cos(theta) + connector.GetLocation().Y * FMath::Sin(theta)),
									   (connector.GetLocation().X * FMath::Sin(theta) + connector.GetLocation().Y * FMath::Cos(theta)),
										connector.GetLocation().Z);*/

		/*spawnTransform.SetRotation(spawnRotation.Quaternion());
		if (theta < 0.25 * 3.14159 && theta > 0) {
			GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, "Quad 1");
			spawnTransform.SetLocation(roomOrigin.GetLocation() + connPosition + newPosition);
		}
		else if (theta > 0.25 * 3.14159) {
			GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, "Quad 2");
			spawnTransform.SetLocation(roomOrigin.GetLocation() + connPosition + newPosition);
		} 
		else  if (theta < -0.25 * 3.14159) {
			GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, "Quad 3");
			spawnTransform.SetLocation(roomOrigin.GetLocation() - connPosition + newPosition);
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, "Quad 3");
			spawnTransform.SetLocation(roomOrigin.GetLocation() - connPosition + newPosition);
		}

		FActorSpawnParameters params;
		//params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		ARoomPrefab* thisRoom = GetWorld()->SpawnActor<ARoomPrefab>(roomToSpawn, spawnTransform, params);

		if (thisRoom) {
			currentRooms.Add(thisRoom);
			return thisRoom;
		}
		else {
			return NULL;
		}*/
		return nullptr;
	}
	else {
		return nullptr;
	}
}