// Fill out your copyright notice in the Description page of Project Settings.


#include "ABasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputAction.h"



UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
UInputMappingContext* DefaultMappingContext;

UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
UInputAction* MoveAction;
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
UInputAction* LookAction;
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
UInputAction* JumpAction;
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
UInputAction* EquipAction;
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
UInputAction* AttackAction;
