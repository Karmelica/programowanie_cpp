// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "MyBaseCharacter.generated.h"

class AMyBaseWeapon;
class UAttributesComponent;

UCLASS(Blueprintable)
class CPPPROGRAMING_API AMyBaseCharacter : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyBaseCharacter();
	virtual void GetHit_Implementation(float DamageAmount) override;

	void SetEquippedWeapon(AMyBaseWeapon* MyBaseWeapon);

	void SetCanAttack(bool bAttack);
	void Die();

protected:
	bool bCanAttack = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAttributesComponent* AttributesComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Attack();

	UFUNCTION()
	virtual void HandleDeath();
	UFUNCTION()
	virtual void GetHitAnim();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	AMyBaseWeapon* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* TakeDamageMontage;
};
