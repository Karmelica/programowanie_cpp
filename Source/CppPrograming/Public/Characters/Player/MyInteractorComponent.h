// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyInteractorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPPROGRAMING_API UMyInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties

	UPROPERTY(EditDefaultsOnly)
	float TraceSphereRadius;
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> IgnoreActors;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UMyInteractorComponent();

private:
	void SphereTrace(FHitResult& SphereHit);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void TryInteract();
};
