// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGenerator.h"


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
		maze.Add(TArray<int>());
		for (int j = 0; j < height; ++j) {
			maze[i].Add(0);
		}
	}
	generateMazeRec(loc);
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
			maze[(int)loc.X][(int)loc.Y] |= adjacentLoc.direction;
			maze[(int)adjacentLoc.vec.X][(int)adjacentLoc.vec.Y] |= getOppositeDirection(adjacentLoc.direction);
			generateMazeRec(adjacentLoc.vec);
		}
	}
}

FString AMazeGenerator::GetMazeString() {
	FString str;
	for (int y = height - 1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			int cell = maze[x][y];
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

