// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedSignature, float, CurrentStamina, float, MaxStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, CurrentHealth, float, MaxHealth);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPPROGRAMING_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float RegenSpeed;

	// Death delegate
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnDeathSignature OnDeath;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnDamageSignature OnTakeDamage;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnStaminaChangedSignature OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnHealthChangedSignature OnHealthChanged;

protected:

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

	UFUNCTION()
	float CurrentStamina() const { return Stamina; }
	UFUNCTION()
	float CurrentHealth() const { return Health; }

protected:
	UAttributesComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
