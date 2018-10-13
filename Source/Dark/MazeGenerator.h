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
	FVector location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int flags;
};


UENUM(BlueprintType)
enum EDirection {
	North = 1,
	South = 2,
	East  = 4,
	West = 8
};

UCLASS()
class DARK_API AMazeGenerator : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AMazeGenerator();




	struct RelativeVec2 {
		FIntVector vec;
		EDirection direction;
	};


	
private:

	TArray<TArray<int>> rawMaze;
	TSet<FIntVector> visited;


	EDirection getOppositeDirection(EDirection direction);
	TArray<RelativeVec2> getAdjacentCoordinates(const FIntVector& loc);
	void swap(RelativeVec2& first, RelativeVec2& second);



	void generateMazeRec(FIntVector loc);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int width = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int height = 10;

	TArray<TArray<FMazeCell>> maze;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AActor> CellClass;

	UFUNCTION(BlueprintCallable)
	void generateMaze(FIntVector loc);

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
