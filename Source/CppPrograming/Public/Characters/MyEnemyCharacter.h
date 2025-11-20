// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBaseCharacter.h"
#include "MyEnemyCharacter.generated.h"

class AMyPlayerCharacter;
class UPawnSensingComponent;

UCLASS()
class CPPPROGRAMING_API AMyEnemyCharacter : public AMyBaseCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY()
	AMyPlayerCharacter* PlayerCharacter;

protected:

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UPawnSensingComponent* AIComponent;

private:
protected:

	AMyEnemyCharacter();
};
