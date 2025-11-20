// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UMyUserWidget;
class UInputMappingContext;

UCLASS()
class CPPPROGRAMING_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "UI")
	UMyUserWidget* PlayerHUD;

protected:
	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TArray<UInputMappingContext*> DefaultMappingContexts;

protected:
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
};
