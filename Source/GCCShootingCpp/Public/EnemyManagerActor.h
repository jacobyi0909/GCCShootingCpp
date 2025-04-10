// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManagerActor.generated.h"

UCLASS()
class GCCSHOOTINGCPP_API AEnemyManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 일정시간마다 적공장에서 적을 만들어서 생성 위치에 배치하고 싶다.
	// 속성 : 현재시간, 목표시간, 적 공장, 생성 위치
	float CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MakeTime = 2.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AEnemyActor> EnemyFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* Point;

	UFUNCTION(BlueprintCallable)
	void MakeEnemy();

	FTimerHandle MakeEnemyTimerHandle;


};

