// Fill out your copyright notice in the Description page of Project Settings.
#include "ProceduralGameMode.h"

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

void AProceduralGameMode::GenerateSpawn() {
	if (F1_Spawns.Num() > 0) {
		int numOptions = F1_Spawns.Num();
		int roomToPick = FMath::RandRange(0, numOptions - 1);
		GetWorld()->SpawnActor(F1_Spawns[roomToPick]);
	}
}