// Fill out your copyright notice in the Description page of Project Settings.

#include "DelegateTest.h"


// Sets default values
ADelegateTest::ADelegateTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADelegateTest::BeginPlay()
{
	Super::BeginPlay();
	OnOpen.Broadcast();
}

// Called every frame
void ADelegateTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

