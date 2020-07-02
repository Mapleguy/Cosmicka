// Fill out your copyright notice in the Description page of Project Settings.
#include "RoomConnector.h"
#include "Components/ArrowComponent.h"

// Sets default values for this component's properties
URoomConnector::URoomConnector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward"));
}


// Called when the game starts
void URoomConnector::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void URoomConnector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}