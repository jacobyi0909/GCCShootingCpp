// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TailActor.generated.h"

UCLASS()
class GCCSHOOTINGCPP_API ATailActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATailActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 충돌체와 외형을 만들고싶다.
	// 충돌체를 루트로하고 외형을 루트에 붙이고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComp;

	// 목적지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 450.f;
	

};
