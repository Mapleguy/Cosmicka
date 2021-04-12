// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

AElevator::AElevator() {
	interactMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interact"));
	platformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
}

void AElevator::Interact() {
	ToggleElevator();
}

void AElevator::ToggleElevator_Implementation() {

}