// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"

#include "EnemyActor.h"
#include "Components/ArrowComponent.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Point = CreateDefaultSubobject<UArrowComponent>(TEXT("Point"));
	Point->SetupAttachment(Root);
	Point->SetRelativeRotation(FRotator(-90.f, 0, 180.f));
}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(MakeEnemyTimerHandle, this,
		&AEnemyManagerActor::MakeEnemy, MakeTime, true);
	
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 일정시간마다 적공장에서 적을 만들어서 생성 위치에 배치하고 싶다.
	// // 1. 시간이 흐르다가
	// CurrentTime += DeltaTime;
	// // 2. 현재시간이 생성시간이 되면
	// if (CurrentTime > MakeTime)
	// {
	// 	// 3. 현재시간을 초기화하고
	// 	CurrentTime = 0;
	// 	// 4. 적을 생성하고싶다.
	// 	MakeEnemy();
	// }
}

void AEnemyManagerActor::MakeEnemy()
{
	GEngine->AddOnScreenDebugMessage(0, 3, FColor::Cyan, TEXT("MakeEnemy"));
	
	if (nullptr == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		// 주인공이 없다면 타이머를 멈추고 싶다.
		GetWorld()->GetTimerManager().ClearTimer(MakeEnemyTimerHandle);
		return;
	}
	GetWorld()->SpawnActor<AEnemyActor>(EnemyFactory, Point->GetComponentTransform());
}
