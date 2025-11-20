// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Player/MyPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/UserWidget.h"
#include "Characters/MyBaseCharacter.h"
#include "Characters/Player/UI/MyUserWidget.h"


void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUD)
	{
		PlayerHUD->AddToViewport();
	}

}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Add Input Mapping Contexts
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
