// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

#include "Components/TextBlock.h"

void UScoreWidget::UpdateScore(int32 score, int32 highScore)
{
	TextHighScore->SetText(FText::AsNumber(highScore));
	TextScore->SetText(FText::AsNumber(score));
}
