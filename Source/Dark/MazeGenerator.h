// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Set.h"
#include "Components/StaticMeshComponent.h"
#include "MazeGenerator.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMazeDelegate);

UCLASS()
class DARK_API AMazeGenerator : public AActor
{
	GENERATED_BODY()



public:

	// Sets default values for this actor's properties
	AMazeGenerator();

	UPROPERTY(BlueprintAssignable)
	FMazeDelegate OnMazeGenerated;


protected:

	enum EDirection {
		North = 1,
		South = 2,
		East = 4,
		West = 8
	};

	// Structure containing an FIntVector and an enum representing which direction the next cell is relative to the current one.
	struct RelativeVec2 {
		FIntVector vec;
		EDirection direction;
	};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int width = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int height = 10;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AActor> CellClass;

	UFUNCTION(BlueprintCallable)
	void generateMaze(FIntVector loc);


	
private:

	// Matrix of integers representing which sides of the cell are open via a bitflag. See EDirection
	TArray<TArray<int>> mazeData;
	// Used for the depth-first traversal
	TSet<FIntVector> visited;


	EDirection getOppositeDirection(EDirection direction);
	TArray<RelativeVec2> getAdjacentCoordinates(const FIntVector& loc);


	void swap(RelativeVec2& first, RelativeVec2& second);
	// DFS maze generation implementation
	void generateMazeRec(FIntVector loc);
	// Actually spawns the cells in the game world
	bool spawnMazeCells();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	



	// Called every frame
	virtual void Tick(float DeltaTime) override;




	
};
