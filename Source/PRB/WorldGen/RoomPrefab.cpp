// Fill out your copyright notice in the Description page of Project Settings.
#include "RoomPrefab.h"
#include "RoomConnector.h"
#include "Components/ArrowComponent.h"
#include "RoomDoorway.h"

// Sets default values
ARoomPrefab::ARoomPrefab()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	for (int32 i = 0; i < connCount; i++) {
		FString theName = "Conn " + i;
		CreateDefaultSubobject<URoomConnector>(FName(*theName));
	}

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(baseMesh);
}

// Called when the game starts or when spawned
void ARoomPrefab::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARoomPrefab::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

URoomConnector* ARoomPrefab::GetConnectionPoint(int connector){
	return connectionPoints[connector];
}

int ARoomPrefab::GetConnectionCount() {
	return connectionPoints.Num();
}