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

	// MakeBullet이 호출되면 총알발사 소리를 출력하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AutoFireUseTimer;
	// 자동 총쏘기 기능을 만들고싶다.
	// 마우스 왼쪽 버튼을 누르고 있으면 총알이 0.25초마다 발사되게 하고싶다.
	// 자동총쏘기가 활성 / 비활성
	bool bAutoFire;
	// 시간이 흐르다가 발사 시간이 되면
	float CurrentTime;
	float MakeBulletTime = 0.25f;

	FTimerHandle MakeBulletTimerHandle;


	// 체력을 갖고싶다.
	// 현재체력, 최대체력
	// 태어날 때
	//  - 현재체력을 최대체력으로 하고싶다.  
	//  - PlayerHPWidget을 생성해서 기억하고싶다.
	// 적과 플레이어가 부딪히면 체력을 1 감소하고 UI도 갱신하고싶다.
	// 만약 체력이 0이하라면 파괴되게 하고싶다.
	int32 CurHP;

	int32 MaxHP = 3;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PlayerHPWidgetFactory;

	UPROPERTY(EditAnywhere)
	class UPlayerHPWidget* PlayerHPWidget;

	void MyTakeDamage(int32 damage);
};

