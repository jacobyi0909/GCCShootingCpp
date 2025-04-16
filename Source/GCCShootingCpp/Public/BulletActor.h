// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class GCCSHOOTINGCPP_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION()
	void OnMyBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// 충돌체와 외형
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComp;

	// 이동크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 1000.f;

	// 내가 파괴될 때 소리를 출력하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* ExplosionSFX;

	// 적과 부딪히면 폭발VFX를 표현하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* ExplosionVFX;


	void SetActive(bool isActive);

	// 총알이 어딘가 부딪히면 파괴되지 않고 주인공의 탄창에 다시 들어가고싶다.
	void ReturnToMagazine();
};

