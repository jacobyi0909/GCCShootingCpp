// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingActor.h"

// Sets default values
ACodingActor::ACodingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodingActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Hello World!!"));
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Cyan, TEXT("Hello World!!"));
}

// Called every frame
void ACodingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

