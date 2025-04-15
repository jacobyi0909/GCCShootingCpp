// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class GCCSHOOTINGCPP_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonRestart;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonQuit;

	UFUNCTION()
	void OnMyRestart();

	UFUNCTION()
	void OnMyQuit();
	
};
