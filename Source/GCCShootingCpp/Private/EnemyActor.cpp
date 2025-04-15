// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "PlayerPawn.h"
#include "ShootingGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystem.h"

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

	// 충돌 설정을 하고싶다.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	BoxComp->SetGenerateOverlapEvents(true);

	// preset으로 반영하고싶다.
	BoxComp->SetCollisionProfileName(TEXT("Enemy"));

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
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnMyBoxCompBeginOverlap);
	
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
	// 향하는 방향으로 회전하고싶다.
	FRotator newRotation = UKismetMathLibrary::MakeRotFromXZ(Direction, GetActorUpVector());
	SetActorRotation(newRotation);
	
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

void AEnemyActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


}

void AEnemyActor::OnMyBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 너죽고 나죽자
	// 상대가 주인공이라면

	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	if (player)
	{
		// 주인공의 체력을 1 감소하고싶다.
		player->MyTakeDamage(1);
		// 만약 주인공의 체력이 0 이하라면
		if (player->CurHP <= 0)
		{
			// 주인공을 파괴 하고싶다.
			player->Destroy();

			// 게임모드의 ShowGameOverWidget기능을 호출하고싶다.
			auto* gm = Cast<AShootingGameMode>(GetWorld()->GetAuthGameMode());
			gm->ShowGameOverWidget();
		}

		// 소리를 출력하고싶다.
		UGameplayStatics::PlaySound2D(GetWorld(), ExplosionSFX);
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionVFX,
			this->GetActorLocation()
		);
	}
	this->Destroy();

	

	// if (OtherActor->IsA<APlayerPawn>())
	// {
	// 	
	// }
	// else if (OtherActor->IsA<ABulletActor>())
	// {
	// 	
	// }
	//
	//
	// APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	// if (player)
	// {
	// 	// 성공
	// 	OtherActor->Destroy();
	// }
	// else
	// {
	// 	// player가 nullptr이다.
	// 	ABulletActor* bullet = Cast<ABulletActor>(OtherActor);
	// 	if (bullet)
	// 	{
	// 		
	// 	}
	// }
	// this->Destroy();
}
