// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyZoneActor.h"

#include "Components/BoxComponent.h"

// Sets default values
ADestroyZoneActor::ADestroyZoneActor()
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

	// 충돌 설정을 하고싶다.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	BoxComp->SetGenerateOverlapEvents(true);

	// preset으로 반영하고싶다.
	BoxComp->SetCollisionProfileName(TEXT("DestroyZone"));
}

// Called when the game starts or when spawned
void ADestroyZoneActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this,
		&ADestroyZoneActor::OnMyBoxCompBeginOverlap);
}

// Called every frame
void ADestroyZoneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyZoneActor::OnMyBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();
}

