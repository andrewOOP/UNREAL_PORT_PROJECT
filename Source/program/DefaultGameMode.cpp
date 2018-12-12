// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultGameMode.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

void ADefaultGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void ADefaultGameMode::ChangeMenuWidget(UUserWidget* NewWidget)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidget != nullptr)
	{
		CurrentWidget = NewWidget;
		CurrentWidget->AddToViewport();
	}
}