// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Player/MyPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/UserWidget.h"
#include "Characters/Player/AttributesComponent.h"
#include "Characters/Player/MyPlayerCharacter.h"
#include "Characters/Player/UI/MyUserWidget.h"


void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (PlayerHUD)
	{
		PlayerHUD->AddToViewport();
	}
	PlayerCharacter = Cast<AMyPlayerCharacter>(InPawn);
	if (PlayerCharacter)
	{
		AttributesComponent = PlayerCharacter->GetAttributesComponent();

		AttributesComponent->OnHealthChanged.AddDynamic(PlayerHUD, &UMyUserWidget::UpdateHealth);
		AttributesComponent->OnStaminaChanged.AddDynamic(PlayerHUD, &UMyUserWidget::UpdateStamina);
	}
}

	void AMyPlayerController::SetupInputComponent()
	{
		Super::SetupInputComponent();
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
