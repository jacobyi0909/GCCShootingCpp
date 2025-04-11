// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

#include "EnemyActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 충돌체를 생성해서 루트로 설정 하고싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	BoxComp->SetBoxExtent(FVector(37.5f, 12.5f, 50.f));

	// 메시를 생성해서 루트에 붙이고싶다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeScale3D(FVector(0.75f, 0.25f, 0));

	// 충돌 설정을 하고싶다.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempMesh.Succeeded())
	{
		MeshComp->SetStaticMesh(tempMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterial> tempMeshMat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (tempMeshMat.Succeeded())
	{
		MeshComp->SetMaterial(0, tempMeshMat.Object);
	}
	
	BoxComp->SetGenerateOverlapEvents(true);

	// preset으로 반영하고싶다.
	BoxComp->SetCollisionProfileName(TEXT("Bullet"));

	ConstructorHelpers::FObjectFinder<USoundWave> tempExpSFX(TEXT("/Script/Engine.SoundWave'/Game/Shooting/Sound/Explosion.Explosion'"));
	if (tempExpSFX.Succeeded())
	{
		ExplosionSFX = tempExpSFX.Object;
	}

	ConstructorHelpers::FObjectFinder<UParticleSystem> tempExpVFX(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (tempExpVFX.Succeeded())
	{
		ExplosionVFX = tempExpVFX.Object;
	}
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnMyBoxCompBeginOverlap);
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector dir = GetActorForwardVector();

	SetActorLocation(GetActorLocation() + dir * Speed * DeltaTime);
}

void ABulletActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

void ABulletActor::OnMyBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 너죽고 나죽자
	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy)
	{
		OtherActor->Destroy();
		// 소리를 출력하고싶다.
		UGameplayStatics::PlaySound2D(GetWorld(), ExplosionSFX);
		// vfx를 표현하고싶다.
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionVFX,
			enemy->GetActorLocation()
		);
	}
	this->Destroy();
}


