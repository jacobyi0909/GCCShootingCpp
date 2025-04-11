// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "BulletActor.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

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

	// 충돌 설정을 하고싶다.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	BoxComp->SetGenerateOverlapEvents(true);

	// preset으로 반영하고싶다.
	BoxComp->SetCollisionProfileName(TEXT("Player"));

	// BoxComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	// BoxComp->SetCollisionObjectType(ECC_GameTraceChannel1);
	// BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// BoxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);


	// FireSFX의 값을 로드해서 넣어주고싶다.
	//TEXT("/Script/Engine.SoundWave'/Game/Shooting/Sound/Audio_Bullet.Audio_Bullet'")
	ConstructorHelpers::FObjectFinder<USoundWave> tempFireSFX(
		TEXT("/Script/Engine.SoundWave'/Game/Shooting/Sound/Audio_Bullet.Audio_Bullet'"));
	if (tempFireSFX.Succeeded())
	{
		FireSFX = tempFireSFX.Object;
	}
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

	if (false == AutoFireUseTimer)
	{
		// 만약 자동총쏘기 기능이 활성화 되었다면
		if (bAutoFire)
		{
			// 시간이 흐르다가
			CurrentTime += DeltaTime;
			// 만약 현재시간이 총쏠 시간이되면
			if (CurrentTime > MakeBulletTime)
			{
				//   총알을 만들고
				MakeBullet();
				//   현재시간을 초기화 하고싶다.
				CurrentTime = 0.0f;
			}
		}
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::OnAxisHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::OnAxisVertical);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerPawn::OnActionFirePressed);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &APlayerPawn::OnActionFireReleased);
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
	// 자동총쏘기 기능을 활성화 하고싶다.
	if (AutoFireUseTimer)
	{
		// 타이머를 등록하고싶다.
		GetWorldTimerManager().SetTimer(
			MakeBulletTimerHandle,
			this,
			&APlayerPawn::MakeBullet,
			MakeBulletTime, true
		);
	}
	else
	{
		// 현재시간을 초기화 하고 총알을 미리 하나 만들고싶다.
		bAutoFire = true;
		CurrentTime = 0;
	}
	
	MakeBullet();
}

void APlayerPawn::OnActionFireReleased()
{
	// 자동총쏘기 기능을 비활성화 하고싶다.
	if (AutoFireUseTimer)
	{
		// 타이머를 취소하고싶다.
		GetWorldTimerManager().ClearTimer(MakeBulletTimerHandle);
	}
	else
	{
		bAutoFire = false;
	}
}

void APlayerPawn::MakeBullet()
{
	// 총알공장에서 총알을 하나 생성해서 총구위치에 배치하고싶다.
	FTransform t = FirePoint->GetComponentTransform();
	GetWorld()->SpawnActor<ABulletActor>(BulletFactory, t);

	// 소리를 출력하고싶다.
	UGameplayStatics::PlaySound2D(GetWorld(), FireSFX);
}
