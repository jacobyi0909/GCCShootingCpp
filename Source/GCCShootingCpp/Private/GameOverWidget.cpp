// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼에 내 기능을 연결하고 싶다.
	ButtonRestart->OnClicked.AddDynamic(this, &UGameOverWidget::OnMyRestart);
	ButtonQuit->OnClicked.AddDynamic(this, &UGameOverWidget::OnMyQuit);
}

void UGameOverWidget::OnMyRestart()
{
	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(*levelName));
}

void UGameOverWidget::OnMyQuit()
{
	auto* pc = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), pc, EQuitPreference::Quit, false);
}
