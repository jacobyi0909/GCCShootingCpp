// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

// 전방선언
class UBoxComponent;

UCLASS()
class GCCSHOOTINGCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 충돌체와 외형을 만들고싶다.
	// 전방선언
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500.f;


	void OnAxisHorizontal(float value);
	void OnAxisVertical(float value);

	float H;
	float V;

	// 만약 마우스 왼쪽 버튼이 눌리면
	void OnActionFirePressed();
	void OnActionFireReleased();
	// 총알공장에서 총알을 하나 생성해서 총구위치에 배치하고싶다.
	void MakeBullet();
	// 총알공장
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABulletActor> BulletFactory;
	// 총구위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* FirePoint;
};

