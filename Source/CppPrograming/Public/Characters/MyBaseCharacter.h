#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "MyBaseCharacter.generated.h"

enum class EPawnState : uint8;
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

	void Die();

protected:
	bool bCanAttack = true;

	UFUNCTION(BlueprintCallable, Category="Combat")
	void SetCanAttack(bool bAttack);

	UFUNCTION(BlueprintCallable, Category="Combat")
	bool GetCanAttack() const { return bCanAttack; }

	UFUNCTION(BlueprintCallable, Category="Hitbox")
	void SetWeaponHitbox(bool bActive);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAttributesComponent* AttributesComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Attack();
	virtual void Jump() override;

	UFUNCTION()
	virtual void HandleDeath();
	UFUNCTION()
	virtual void GetHitAnim();

	UFUNCTION(BlueprintCallable)
	void DamageTaken();
	UFUNCTION(BlueprintCallable)
	void DamageTakenEnd();

public:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EPawnState CurrentState;

	UFUNCTION()
	UAttributesComponent* GetAttributesComponent() const { return AttributesComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	AMyBaseWeapon* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* TakeDamageMontage;
};
