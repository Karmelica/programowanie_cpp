// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"


class UProgressBar;

UCLASS()
class CPPPROGRAMING_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;

protected:

public:
	void UpdateHealth(float Current, float Max);
	void UpdateStamina(float Current, float Max);
};
