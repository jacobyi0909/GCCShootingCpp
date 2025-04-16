// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "BulletActor.h"
#include "PlayerHPWidget.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

	// 태어날 때
	//  - 현재체력을 최대체력으로 하고싶다.  
	CurHP = MaxHP;
	//  - PlayerHPWidget을 생성해서 기억하고싶다.
	PlayerHPWidget = Cast<UPlayerHPWidget>(CreateWidget(GetWorld(), PlayerHPWidgetFactory));

	// PlayerHPWidgetFactory가 nullptr이거나? PlayerHPWidgetFactory가 UPlayerHPWidget를 상속받지않았다면...
	check(PlayerHPWidget)

	PlayerHPWidget->AddToViewport();


	Magazine.Empty(MaxBulletCount);
	for (int32 i = 0; i < MaxBulletCount; i++)
	{
		ABulletActor* bullet = GetWorld()->SpawnActor<ABulletActor>(BulletFactory);
		// bullet을 세상에서 존재하지 않게 하고 싶다. -> 비활성화 하고싶다.
		bullet->SetActive(false);
		Magazine.Add(bullet);
	}
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

	PlayerInputComponent->BindAction(TEXT("FireRound"), IE_Pressed, this, &APlayerPawn::OnActionFireRound);
	PlayerInputComponent->BindAction(TEXT("FireRoundInterval"), IE_Pressed, this, &APlayerPawn::OnActionFireRoundInterval);
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
	MakeBullet(FVector::ZeroVector, false);
}

ABulletActor* APlayerPawn::MakeBullet(FVector location, bool bFireRound)
{
	// Magazine에 총알이 들어있지 않으면 바로 종료
	if (Magazine.Num() <= 0)
	{
		return nullptr;
	}

	// 탄창에서 총알을 하나 가져와서 활성처리 하고싶다.
	auto* bullet = Magazine[0];

	if (bFireRound)
	{
		bullet->SetActorLocation(location);
	}
	else
	{
		FTransform t = FirePoint->GetComponentTransform();
		bullet->SetActorTransform(t);
	}
	bullet->SetActive(true);

	// 탄창에서 제거하고싶다.
	Magazine.RemoveAt(0);


	// 소리를 출력하고싶다.
	UGameplayStatics::PlaySound2D(GetWorld(), FireSFX);

	return bullet;
}

void APlayerPawn::MyTakeDamage(int32 damage)
{
	CurHP -= damage;
	PlayerHPWidget->UpdateHPBar(CurHP, MaxHP);
}

void APlayerPawn::OnActionFireRound()
{
	float angle = 15.0f;
	FQuat rot = GetActorQuat();
	FVector up = GetActorUpVector();

	FQuat addAngle = FRotator(0, 0, angle).Quaternion();

	for (float i = 0; i < 360; i += angle)
	{
		FVector loc = GetActorLocation() + (rot * up) * 50.f;
		auto* bullet = MakeBullet(loc, true);
		if (bullet)
		{
			FVector newDir = (rot * up).GetSafeNormal();
			FVector bulletUp = -GetActorForwardVector();
			bullet->SetActorRotation(UKismetMathLibrary::MakeRotFromXZ(newDir, bulletUp));
		}
		rot *= addAngle;
	}
}

void APlayerPawn::OnActionFireRoundInterval()
{
	FTimerHandle handle;
	StartRot = GetActorQuat();
	AngleRoundInterval = 0;
	GetWorldTimerManager().SetTimer(handle, this, &APlayerPawn::MakeBulletRoundInterval, 0.01f, false);

}

void APlayerPawn::MakeBulletRoundInterval()
{
	float angle = 15.0f;
	FVector up = GetActorUpVector();

	FQuat addAngle = FRotator(0, 0, angle).Quaternion();

	FVector loc = GetActorLocation() + (StartRot * up) * 50.f;
	auto* bullet = MakeBullet(loc, true);
	if (bullet)
	{
		FVector newDir = (StartRot * up).GetSafeNormal();
		FVector bulletUp = -GetActorForwardVector();
		bullet->SetActorRotation(UKismetMathLibrary::MakeRotFromXZ(newDir, bulletUp));
	}
	StartRot *= addAngle;
	AngleRoundInterval += angle;
	if (AngleRoundInterval < 360.0f * 2)
	{
		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, this, &APlayerPawn::MakeBulletRoundInterval, 0.01f, false);
	}
}
