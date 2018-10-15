// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGenerator.h"
#include "Engine/World.h"
#include "Cell.h"

#define PRINT(x) UE_LOG(LogTemp, Warning, TEXT(x))
#define PRINT_DEC(x) UE_LOG(LogTemp, Warning, TEXT("%d"), x)


// Sets default values
AMazeGenerator::AMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMazeGenerator::EDirection AMazeGenerator::getOppositeDirection(AMazeGenerator::EDirection direction)
{
	switch (direction)
	{
		case North:
			return South;
			break;
		case South:
			return North;
			break;
		case East:
			return West;
			break;
		case West:
			return East;
			break;
		default:
			break;
	}
	return North;
}

TArray<AMazeGenerator::RelativeVec2> AMazeGenerator::getAdjacentCoordinates(const FIntVector& loc)
{
	TArray<RelativeVec2> adj;
	if (loc.X > 0)
		adj.Add(RelativeVec2{ FIntVector(loc.X - 1, loc.Y, 0), West });
	if (loc.X < width - 1)
		adj.Add(RelativeVec2{ FIntVector(loc.X + 1, loc.Y, 0), East });
	if (loc.Y > 0)
		adj.Add(RelativeVec2{ FIntVector(loc.X, loc.Y - 1, 0), South });
	if (loc.Y < height - 1)
		adj.Add(RelativeVec2{ FIntVector(loc.X, loc.Y + 1, 0), North });
	return adj;
}

void AMazeGenerator::swap(RelativeVec2& first, RelativeVec2& second)
{
	auto temp = first;
	first = second;
	second = temp;
}

void AMazeGenerator::generateMaze(FIntVector loc)
{
	for (int i = 0; i < width; ++i) {
		mazeData.Add(TArray<int>());
		for (int j = 0; j < height; ++j) {
			mazeData[i].Add(0);
		}
	}
	generateMazeRec(loc);
	if (spawnMazeCells()) {
		OnMazeGenerated.Broadcast();
	}
}

void AMazeGenerator::generateMazeRec(FIntVector loc)
{
	visited.Add(loc);
	auto coords = getAdjacentCoordinates(loc);

	for (int i = coords.Num() - 1; i > 0; --i) {
		int j = FMath::RandRange(0, i);
		swap(coords[i], coords[j]);
	}


	for (const RelativeVec2& adjacentLoc : coords) {
		if (!visited.Contains(adjacentLoc.vec)) {
			mazeData[loc.X][loc.Y] |= adjacentLoc.direction;
			mazeData[adjacentLoc.vec.X][adjacentLoc.vec.Y] |= getOppositeDirection(adjacentLoc.direction);
			generateMazeRec(adjacentLoc.vec);
		}
	}
}

bool AMazeGenerator::spawnMazeCells()
{
	if (!CellClass) {
		PRINT("No cell class has been assigned");
		return false;
	}

	FVector pos(0, 0, 0);
	AActor* refCell = GetWorld()->SpawnActor(*CellClass, &pos);

	FBox box = refCell->GetComponentsBoundingBox();
	FVector cellSize = box.GetSize();

	refCell->Destroy();

	// Generate a 2d array of {FVector position, int openFlags}  
	for (int i = 0; i < mazeData.Num(); ++i) {
		for (int j = 0; j < mazeData[i].Num(); ++j) {

			int flags = mazeData[i][j];
			FVector location(i * cellSize.X, j * cellSize.Y, 0);

			ACell* spawnedCell = (ACell*)GetWorld()->SpawnActor(*CellClass, &location);
			if (!spawnedCell) {
				PRINT("Unable to spawn a maze cell");
				return false;
			}


			// We don't destroy the cooresponding walls, but rather the wall 90 degrees cw from it
			// This is to account for rotating axes between Y being up to UE4's X being forward
			if (flags & North) {
				spawnedCell->Right->DestroyComponent();
			}
			if (flags & South) {
				spawnedCell->Left->DestroyComponent();
			}
			if (flags & East) {
				spawnedCell->Front->DestroyComponent();
			}
			if (flags & West) {
				spawnedCell->Back->DestroyComponent();
			}
			spawnedCell->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		}
	}
	return true;
}


// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

