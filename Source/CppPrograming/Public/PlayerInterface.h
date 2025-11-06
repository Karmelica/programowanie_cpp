// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UMyInterface : public UInterface
{
	GENERATED_BODY()
};

class IMyInterface
{
	GENERATED_BODY()

public:
	virtual void InteractionInterface() = 0;
};
