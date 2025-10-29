// Fill out your copyright notice in the Description page of Project Settings.


#include "ABasePlayerCharacter.h"

void AABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Test message 123"));
}