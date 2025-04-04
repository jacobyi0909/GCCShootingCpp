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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyEditAnywhere = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MyEditDefaultsOnly = 10;
	UPROPERTY(EditInstanceOnly)
	int32 MyEditInstanceOnly = 10;

	UPROPERTY(VisibleAnywhere)
	int32 MyVisibleAnywhere = 10;
	UPROPERTY(VisibleDefaultsOnly)
	int32 MyVisibleDefaultsOnly = 10;
	UPROPERTY(VisibleInstanceOnly)
	int32 MyVisibleInstanceOnly = 10;

	// 블루프린트에서 출력하세요.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Num = 10;
	// 실수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500.f;
	// 논리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGood = true;
	// 문자열
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MyName = TEXT("이영훈");


	// 함수
// - BlueprintCallable
// - BlueprintPure
// - BlueprintImplementableEvent
// - BlueprintNativeEvent
	UFUNCTION(BlueprintCallable)
	int32 AddCallable(int32 a, int32 b);
	UFUNCTION(BlueprintPure)
	int32 AddPure(int32 a, int32 b);


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	int32 AddImplEvent(int32 a, int32 b);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 AddNativeEvent(int32 a, int32 b);
};

