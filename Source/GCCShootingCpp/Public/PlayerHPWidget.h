// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class GCCSHOOTINGCPP_API UPlayerHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 태어날 때 HPBar의 값을 최대값으로 하고싶다.
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPBar;
	
	// HPBar의 값을 갱신하는 기능을 만들고싶다.
	void UpdateHPBar(float cur, float max);	
	
};
