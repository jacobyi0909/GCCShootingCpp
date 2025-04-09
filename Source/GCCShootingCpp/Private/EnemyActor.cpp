// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	BoxComp->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	// 태어날 때 방향을 정하고
	int32 rv = FMath::RandRange(0, 99);
	//  - 30%확률로 플레이어 방향, 나머지 확률로 앞 방향으로 정하고 싶다.
	if (rv < 30)
	{
		// 플레이어 방향
		auto* player = GetWorld()->GetFirstPlayerController()->GetPawn();
		Direction = player->GetActorLocation() - this->GetActorLocation();
		Direction.Normalize();
	}
	else
	{
		// 앞 방향
		Direction = GetActorForwardVector();
	}
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 살아가면서 그 방향으로 이동하고 싶다.
	// P = P0 + vt
	FVector newLocation = GetActorLocation() + Direction * Speed * DeltaTime;
	SetActorLocation(newLocation);
}
