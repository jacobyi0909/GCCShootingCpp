// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameMode.h"

#include "GameOverWidget.h"
#include "ScoreWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

void AShootingGameMode::BeginPlay()
{
	Super::BeginPlay();
	// 태어날 때 점수를 0점으로 처리하고싶다.
	Score = 0;
	// 태어날 때 UI를 만들어서

	ScoreWidget = Cast<UScoreWidget>(CreateWidget(GetWorld(), ScoreWidgetFactory));

	// ScoreWidgetFactory를 채우지 않거나 상속관계가 아니라면
	check(ScoreWidget != nullptr);

	// 화면에 보이게하고싶다.
	if (ScoreWidget)
	{
		ScoreWidget->AddToViewport();
	}
	
	// 인풋모드 GameOnly
	auto* pc = GetWorld()->GetFirstPlayerController();
	pc->SetShowMouseCursor(false);
	pc->SetInputMode(FInputModeGameOnly());

}

void AShootingGameMode::AddScore(int32 Point)
{
	// 점수를 Point만큼 증가시키고
	Score += Point;
	// UI에 점수를 반영하고싶다.
	ScoreWidget->TextScore->SetText(FText::AsNumber(Score));
}

void AShootingGameMode::ShowGameOverWidget()
{
	GameOverWidget = Cast<UGameOverWidget>(CreateWidget(GetWorld(), GameOverWidgetFactory));

	check(GameOverWidget != nullptr);

	// 화면에 보이게하고싶다.
	if (GameOverWidget)
	{
		GameOverWidget->AddToViewport();
	}

	// 인풋모드 UIOnly
	auto* pc = GetWorld()->GetFirstPlayerController();
	pc->SetShowMouseCursor(true);
	pc->SetInputMode(FInputModeUIOnly());
}
