// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInterface.h"
#include "GameFramework/Actor.h"
#include "MyItem.generated.h"

UCLASS(Blueprintable)
class CPPPROGRAMING_API AMyItem : public AActor, public IMyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void InteractionInterface() override;
	void PickUp();

};
