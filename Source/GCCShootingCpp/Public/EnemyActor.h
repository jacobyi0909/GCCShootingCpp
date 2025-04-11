// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class GCCSHOOTINGCPP_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 충돌처리
	// 1. Actor기반
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	// 2. Component기반
	UFUNCTION()
	void OnMyBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	

	// 충돌체와 외관을 만들고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComp;

	FVector Direction;
	float Speed = 500.f;
	
	// 태어날 때 방향을 정하고
	//  - 30%확률로 플레이어 방향, 나머지 확률로 앞 방향으로 정하고 싶다.
	// 살아가면서 그 방향으로 이동하고 싶다.

	// 내가 파괴될 때 소리를 출력하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* ExplosionSFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* ExplosionVFX;
};
