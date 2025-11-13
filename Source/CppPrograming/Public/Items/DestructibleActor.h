// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/CombatInterface.h"
#include "DestructibleActor.generated.h"

class UCapsuleComponent;

UCLASS()
class CPPPROGRAMING_API ADestructibleActor : public AActor, public ICombatInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleActor();

private:
	int HitPoints = 2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetHit_Implementation(float Damage) override;
	virtual void Bonk();
public:

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ObjectMesh;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
