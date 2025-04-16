// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameMode.h"

#include "GameOverWidget.h"
#include "HighScoreSaveGame.h"
#include "ScoreWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

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

	// 최고점수를 읽어온다.
	LoadHighScore();
	// 현재점수와 최고점수를 UI에 반영하고싶다.
	ScoreWidget->UpdateScore(Score, HighScore);
}

void AShootingGameMode::AddScore(int32 Point)
{
	// 점수를 Point만큼 증가시키고
	Score += Point;

	// 만약 Score가 HighScore보다 크다면
	if (Score>HighScore)
	{
		// HighScore를 Score값으로 대입하고싶다.
		HighScore = Score;
		// SaveHighScore 기능을 호출하고싶다.
		SaveHighScore();
	}
	
	// UI에 점수를 반영하고싶다.
	ScoreWidget->UpdateScore(Score, HighScore);
}

void AShootingGameMode::SaveHighScore_Implementation()
{
	auto* sg = Cast<UHighScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UHighScoreSaveGame::StaticClass()));
	if (sg)
	{
		sg->SaveHighScore = HighScore;
		UGameplayStatics::SaveGameToSlot(sg, SaveGameSlotName, SaveGameSlotIndex);
	}
}

void AShootingGameMode::LoadHighScore_Implementation()
{
	if (false == UGameplayStatics::DoesSaveGameExist(SaveGameSlotName, SaveGameSlotIndex))
	{
		HighScore = 0;
		return;
	}
	
	auto* sg = Cast<UHighScoreSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, SaveGameSlotIndex));
	if (sg)
	{
		HighScore = sg->SaveHighScore;	
	}
	
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
