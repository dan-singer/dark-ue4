// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.generated.h"

UCLASS()
class DARK_API ACell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACell();

	UPROPERTY(VisibleAnywhere, Instanced)
	UStaticMeshComponent* Front = nullptr;
	UPROPERTY(VisibleAnywhere, Instanced)
	UStaticMeshComponent* Back = nullptr;
	UPROPERTY(VisibleAnywhere, Instanced)
	UStaticMeshComponent* Left = nullptr;
	UPROPERTY(VisibleAnywhere, Instanced)
	UStaticMeshComponent* Right = nullptr;
	UPROPERTY(VisibleAnywhere, Instanced)
	UStaticMeshComponent* Bottom = nullptr;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
