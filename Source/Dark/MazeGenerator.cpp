// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGenerator.h"
#include "Engine/World.h"

#define PRINT(x) UE_LOG(LogTemp, Warning, TEXT(x))
#define PRINT_DEC(x) UE_LOG(LogTemp, Warning, TEXT("%d"), x)


// Sets default values
AMazeGenerator::AMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMazeGenerator::Direction AMazeGenerator::getOppositeDirection(Direction direction)
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

TArray<AMazeGenerator::RelativeVec2> AMazeGenerator::getAdjacentCoordinates(const FVector2D & loc)
{
	TArray<RelativeVec2> adj;
	if (loc.X > 0)
		adj.Add(RelativeVec2{ FVector2D(loc.X - 1, loc.Y), West });
	if (loc.X < width - 1)
		adj.Add(RelativeVec2{ FVector2D(loc.X + 1, loc.Y), East });
	if (loc.Y > 0)
		adj.Add(RelativeVec2{ FVector2D(loc.X, loc.Y - 1), South });
	if (loc.Y < height - 1)
		adj.Add(RelativeVec2{ FVector2D(loc.X, loc.Y + 1), North });
	return adj;
}

void AMazeGenerator::swap(RelativeVec2& first, RelativeVec2& second)
{
	auto temp = first;
	first = second;
	second = temp;
}

void AMazeGenerator::generateMaze(FVector2D loc)
{
	for (int i = 0; i < width; ++i) {
		rawMaze.Add(TArray<int>());
		for (int j = 0; j < height; ++j) {
			rawMaze[i].Add(0);
		}
	}
	generateMazeRec(loc);

	if (!CellClass)
		return;

	FVector pos(0, 0, 0);
	AActor* actor = GetWorld()->SpawnActor(*CellClass, &pos);
	
	FBox box = actor->GetComponentsBoundingBox();
	FVector cellSize = box.GetSize();
	
	// Generate a 2d array of {FVector position, int openFlags}  
	for (int i = 0; i < rawMaze.Num(); ++i) {
		maze.Add(TArray<FMazeCell>());
		for (int j = 0; j < rawMaze[i].Num(); ++j) {
			FMazeCell cell;
			cell.flags = rawMaze[i][j];
			cell.location = FVector2D(i * cellSize.X, j * cellSize.Y);
			maze[i].Add(cell);
		}
	}
	// Provide an accessor to elements of said array for blueprints
	// Loop through array and spawn cells
	// Remove walls based on flags
}

void AMazeGenerator::generateMazeRec(FVector2D loc)
{
	visited.Add(loc);
	auto coords = getAdjacentCoordinates(loc);

	for (int i = coords.Num() - 1; i > 0; --i) {
		int j = FMath::RandRange(0, i);
		swap(coords[i], coords[j]);
	}


	for (const RelativeVec2& adjacentLoc : coords) {
		if (!visited.Contains(adjacentLoc.vec)) {
			rawMaze[(int)loc.X][(int)loc.Y] |= adjacentLoc.direction;
			rawMaze[(int)adjacentLoc.vec.X][(int)adjacentLoc.vec.Y] |= getOppositeDirection(adjacentLoc.direction);
			generateMazeRec(adjacentLoc.vec);
		}
	}
}

FString AMazeGenerator::GetMazeString() {
	FString str;
	for (int y = height - 1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			int cell = rawMaze[x][y];
			str += "[";
			if (cell & North) {
				str += "N";
			}
			if (cell & South) {
				str += "S";
			}
			if (cell & East) {
				str += "E";
			}
			if (cell & West) {
				str += "W";
			}
			str += "] ";
		}
		str += "\n";
	}
	return str;
}

FMazeCell AMazeGenerator::GetCell(int x, int y)
{
	return maze[x][y];
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

