// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyInteractor.generated.h"

class UStaticMeshSocket;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPPROGRAMING_API UMyInteractor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyInteractor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	IInterface* IInteract;

	UPROPERTY(EditAnywhere, Category="Sockets")
	UStaticMeshSocket* TargetSocket;
};
