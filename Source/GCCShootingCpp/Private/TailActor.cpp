// Fill out your copyright notice in the Description page of Project Settings.


#include "TailActor.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATailActor::ATailActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체를 생성해서 루트로 설정 하고싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	BoxComp->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	// 메시를 생성해서 루트에 붙이고싶다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATailActor::BeginPlay()
{
	Super::BeginPlay();
	// 태어날 때 목적지에 값이 없으면 목적지를 주인공으로 하고싶다.

	if (nullptr == TargetActor)
	{
		auto* pc = GetWorld()->GetFirstPlayerController();
		TargetActor = pc->GetPawn();
	}
}
void ATailActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 목적지를 향해 계속 이동하고싶다.
	// target <- me
	FVector dir = TargetActor->GetActorLocation() - this->GetActorLocation();
	dir.Normalize();// 원본의 크기를 1로
	// dir.GetSafeNormal() // 사본의 크기를 1로해서 반환
	SetActorLocation(GetActorLocation() + dir.GetSafeNormal() * Speed * DeltaTime);
}

