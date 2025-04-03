// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodingActor.generated.h"

UCLASS()
class GCCSHOOTINGCPP_API ACodingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 정수형 변수 num을 만들어서 10을 넣고싶다.
	int32 Num = 10;
	// 실수
	float Speed = 500.f;
	// 논리
	bool bGood = true;
	// 문자열
	FString MyName = TEXT("이영훈");
};
