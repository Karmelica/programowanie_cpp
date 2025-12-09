// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/AttributesComponent.h"

// Sets default values for this component's properties
UAttributesComponent::UAttributesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = false;

	// Set default values
	MaxHealth = 100.f;
	Stamina = 200.f;
	RegenSpeed = 10.f;

}

// Called when the game starts
void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize health to max health at start
	Health = MaxHealth;
	Stamina = MaxStamina;

	if (OnStaminaChanged.IsBound())
	{
		OnStaminaChanged.Broadcast(Stamina, MaxStamina);
	}
	if (OnHealthChanged.IsBound())
	{
		OnHealthChanged.Broadcast(Health, MaxHealth);
	}
}

// Called every frame
void UAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAttributesComponent::TakeDamage(float DamageAmount)
{
	if (DamageAmount <= 0.0f) return;

	float OldHealth = Health;
	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);

	//UE_LOG(LogTemp, Warning, TEXT("%s took %.2f damage. Health: %.2f / %.2f"), 
	//	*GetOwner()->GetName(), DamageAmount, Health, MaxHealth);

	// Broadcast death if health reached zero
	if (OldHealth > 0.0f && Health <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has died!"), *GetOwner()->GetName());
		if (OnDeath.IsBound())
		{
			OnDeath.Broadcast();
		}
	}
	if (OnTakeDamage.IsBound() && Health > 0.f)
	{
		OnTakeDamage.Broadcast();
	}
	if (OnHealthChanged.IsBound())
	{
		OnHealthChanged.Broadcast(Health, MaxHealth);
	}
}

void UAttributesComponent::DrainStamina(float ActionStamina)
{
	Stamina = FMath::Clamp(Stamina - ActionStamina, 0.0f, MaxStamina);
	if (OnStaminaChanged.IsBound())
	{
		OnStaminaChanged.Broadcast(Stamina, MaxStamina);
	}
}

void UAttributesComponent::RecoverStamina(float RecoveredStamina)
{
	if (Stamina >= MaxStamina || bDraining) return;
	Stamina = FMath::Clamp(Stamina + RecoveredStamina, 0.0f, MaxStamina);
	if (OnStaminaChanged.IsBound())
	{
		OnStaminaChanged.Broadcast(Stamina, MaxStamina);
	}
}

bool UAttributesComponent::SufficientStamina(float ActionStamina) const
{
	return Stamina >= ActionStamina;
}

bool UAttributesComponent::IsAlive() const
{
	return Health > 0.0f;
}

