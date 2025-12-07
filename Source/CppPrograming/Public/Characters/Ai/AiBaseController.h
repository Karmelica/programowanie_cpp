// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AiBaseController.generated.h"

class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class CPPPROGRAMING_API AAiBaseController : public AAIController
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UAISenseConfig_Sight* SightSenseConfig;

protected:
	AAiBaseController();
};
