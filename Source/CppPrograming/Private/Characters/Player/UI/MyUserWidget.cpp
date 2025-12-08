// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/UI/MyUserWidget.h"
#include "Components/ProgressBar.h"


void UMyUserWidget::UpdateHealth(float Current, float Max) 
{
	HealthBar->SetPercent(Current / Max);
}

void UMyUserWidget::UpdateStamina(float Current, float Max) 
{
	StaminaBar->SetPercent(Current / Max);
}
