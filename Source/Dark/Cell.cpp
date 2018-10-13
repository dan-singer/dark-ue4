// Fill out your copyright notice in the Description page of Project Settings.

#include "Cell.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACell::ACell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));

	Front = CreateDefaultSubobject<UStaticMeshComponent>(FName("Front"));
	Front->SetupAttachment(RootComponent);

	Back = CreateDefaultSubobject<UStaticMeshComponent>(FName("Back"));
	Back->SetupAttachment(RootComponent);

	Left = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left"));
	Left->SetupAttachment(RootComponent);

	Right = CreateDefaultSubobject<UStaticMeshComponent>(FName("Right"));
	Right->SetupAttachment(RootComponent);

	Bottom = CreateDefaultSubobject<UStaticMeshComponent>(FName("Bottom"));
	Bottom->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

