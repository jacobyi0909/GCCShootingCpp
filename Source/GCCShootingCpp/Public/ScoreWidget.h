// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class GCCSHOOTINGCPP_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextHighScore;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextScore;

	void UpdateScore(int32 score, int32 highScore);
};
