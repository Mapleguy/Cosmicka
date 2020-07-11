// Fill out your copyright notice in the Description page of Project Settings.
#include "RoomPrefab.h"
#include "RoomConnector.h"
#include "RoomDoorway.h"

// Sets default values
ARoomPrefab::ARoomPrefab()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create root
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(root);

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(root);
}

// Called when the game starts or when spawned
void ARoomPrefab::BeginPlay()
{
	Super::BeginPlay();
	
	GetComponents<URoomConnector>(roomConnectors, true);
}

// Called every frame
void ARoomPrefab::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ARoomPrefab::GetConnectorCount() {
	return roomConnectors.Num();
}

URoomConnector* ARoomPrefab::GetConnector(int num) {
	if (roomConnectors[num]) {
		return roomConnectors[num];
	}
	else {
		return NULL;
	}
}