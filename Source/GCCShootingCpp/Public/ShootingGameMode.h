// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GCCSHOOTINGCPP_API AShootingGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	// 태어날 때 점수를 0점으로 처리하고싶다.
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, blueprintReadWrite)
	int32 Score;
	
	// 태어날 때 UI를 만들어서 화면에 보이게하고싶다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> ScoreWidgetFactory;

	UPROPERTY()
	class UScoreWidget* ScoreWidget;

	// 총알과 적이 부딪혔을 때 점수를 업데이트하고 UI를 갱신하는 기능을 만들고싶다.
	UFUNCTION(Blueprintable)
	void AddScore(int32 Point);



	// 게임오버 처리하고싶다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> GameOverWidgetFactory;

	UPROPERTY()
	class UGameOverWidget* GameOverWidget;

	void ShowGameOverWidget();
};
