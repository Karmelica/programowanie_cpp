// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributesComponent.h"

// Sets default values for this component's properties
UAttributesComponent::UAttributesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = false;

	// Set default values
	MaxHealth = 100.0f;
	Health = MaxHealth;
}


// Called when the game starts
void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize health to max health at start
	Health = MaxHealth;
}


// Called every frame
void UAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UAttributesComponent::GetHealth() const
{
	return Health;
}

float UAttributesComponent::GetMaxHealth() const
{
	return MaxHealth;
}

void UAttributesComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	
	// Check if dead after setting health
	if (Health <= 0.0f && OnDeath.IsBound())
	{
		OnDeath.Broadcast();
	}
}

void UAttributesComponent::TakeDamage(float DamageAmount)
{
	if (DamageAmount <= 0.0f) return;

	float OldHealth = Health;
	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);

	UE_LOG(LogTemp, Warning, TEXT("%s took %.2f damage. Health: %.2f / %.2f"), 
		*GetOwner()->GetName(), DamageAmount, Health, MaxHealth);

	// Broadcast death if health reached zero
	if (OldHealth > 0.0f && Health <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has died!"), *GetOwner()->GetName());
		if (OnDeath.IsBound())
		{
			OnDeath.Broadcast();
		}
	}
}

bool UAttributesComponent::IsAlive() const
{
	return Health > 0.0f;
}
