// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/UI/MyUserWidget.h"

#include "Characters/Player/AttributesComponent.h"
#include "Components/ProgressBar.h"


void UMyUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	/*
	if (AttributesComponent)
	{
		AttributesComponent->OnHealthChanged.AddDynamic(this, &UMyUserWidget::UpdateHealth);
		AttributesComponent->OnStaminaChanged.AddDynamic(this, &UMyUserWidget::UpdateStamina);
	}*/
}

void UMyUserWidget::UpdateHealth(float Current, float Max)
{
	HealthBar->SetPercent(Current / Max);
}

void UMyUserWidget::UpdateStamina(float Current, float Max)
{
	StaminaBar->SetPercent(Current / Max);
}
