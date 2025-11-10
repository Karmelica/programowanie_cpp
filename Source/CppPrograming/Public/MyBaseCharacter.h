// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatInterface.h"
#include "GameFramework/Character.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Attack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAttributesComponent* AttributesComponent;

	UFUNCTION()
	virtual void HandleDeath();

	// Funkcja wywo³ywana po zakoñczeniu animacji œmierci
	UFUNCTION()
	void OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	bool bCanAttack = true;

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

};
