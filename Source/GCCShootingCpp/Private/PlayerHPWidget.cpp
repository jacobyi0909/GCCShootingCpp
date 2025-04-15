// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHPWidget.h"

#include "Components/ProgressBar.h"

void UPlayerHPWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 태어날 때 HPBar을 꽉 채우고싶다.
	HPBar->SetPercent(1.f);
}

void UPlayerHPWidget::UpdateHPBar(float cur, float max)
{
	HPBar->SetPercent(cur / max);
}
