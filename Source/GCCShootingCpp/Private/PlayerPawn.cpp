// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "BulletActor.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체를 생성해서 루트로 설정 하고싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	BoxComp->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	// 메시를 생성해서 루트에 붙이고싶다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(RootComponent);
	FirePoint->SetRelativeLocationAndRotation(FVector(0, 0, 100.f), FRotator(90.f, 0, 0));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// P = P0 + vt
	// 사용자의 입력에따라 상하좌우로 이동하고싶다.
	// 1. 사용자의 입력으로 방향을 만들고싶다.
	//FVector dir = GetActorRightVector();
	FVector dir = FVector(0, H, V);
	dir.Normalize();

	// 2. 그 방향으로 이동하고싶다.
	FVector p0 = GetActorLocation();
	FVector v = dir * Speed;
	float t = DeltaTime;
	SetActorLocation(p0 + v * t);
	
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::OnAxisHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::OnAxisVertical);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerPawn::OnActionFirePressed);
}

void APlayerPawn::OnAxisHorizontal(float value)
{
	H = value;
}

void APlayerPawn::OnAxisVertical(float value)
{
	V = value;
}

void APlayerPawn::OnActionFirePressed()
{
	MakeBullet();
}

void APlayerPawn::OnActionFireReleased()
{
}

void APlayerPawn::MakeBullet()
{
	// 총알공장에서 총알을 하나 생성해서 총구위치에 배치하고싶다.
	FTransform t = FirePoint->GetComponentTransform();
	GetWorld()->SpawnActor<ABulletActor>(BulletFactory, t);
}

