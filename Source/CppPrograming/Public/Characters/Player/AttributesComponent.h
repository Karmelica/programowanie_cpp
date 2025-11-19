// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPPROGRAMING_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "Attributes")
	float Health;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float MaxStamina;

	UPROPERTY(VisibleAnywhere, Category = "Attributes")
	float Stamina;

	bool bDraining;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float RegenSpeed;

	// Apply damage function
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void TakeDamage(float DamageAmount);

	//Drain stamina
	void DrainStamina(float ActionStamina);

	//Recover stamina
	void RecoverStamina(float RecoveredStamina);

	// Check if alive
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsAlive() const;

	bool SufficientStamina(float ActionStamina) const;

	// Death delegate
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnDeathSignature OnDeath;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnDeathSignature OnTakeDamage;
};
