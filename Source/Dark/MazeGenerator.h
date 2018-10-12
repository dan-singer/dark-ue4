// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Set.h"
#include "Components/StaticMeshComponent.h"
#include "MazeGenerator.generated.h"



USTRUCT(BlueprintType)
struct FMazeCell {


	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int flags;
};


UCLASS()
class DARK_API AMazeGenerator : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AMazeGenerator();


	enum Direction {
		North = 1,
		South = 2,
		East = 4,
		West = 8
	};

	struct RelativeVec2 {
		FVector2D vec;
		Direction direction;
	};


	
private:

	TArray<TArray<int>> rawMaze;
	TSet<FVector2D> visited;


	Direction getOppositeDirection(Direction direction);
	TArray<RelativeVec2> getAdjacentCoordinates(const FVector2D& loc);
	void swap(RelativeVec2& first, RelativeVec2& second);



	void generateMazeRec(FVector2D loc);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int width = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int height = 10;

	UPROPERTY(EditAnywhere)
	FVector2D realWorldMultiplier;

	TArray<TArray<FMazeCell>> maze;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AActor> CellClass;

	UFUNCTION(BlueprintCallable)
	void generateMaze(FVector2D loc);

	UFUNCTION(BlueprintCallable)
	FString GetMazeString();

	UFUNCTION(BlueprintCallable)
	FMazeCell GetCell(int x, int y);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
