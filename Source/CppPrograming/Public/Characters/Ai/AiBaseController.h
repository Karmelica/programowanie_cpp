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

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	UObject* SeenActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FVector PlayerLocation;

protected:
	AAiBaseController();
};
