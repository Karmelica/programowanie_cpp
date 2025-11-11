// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInterface.h"
#include "GameFramework/Actor.h"

#include "MyItem.generated.h"

class UCapsuleComponent;

UCLASS(Blueprintable)
class CPPPROGRAMING_API AMyItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AMyItem();

	// Sets default values for this actor's properties
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* Capsule;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation(AActor* OuterActor) override;
};
