// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseCharacter.h"
#include "MyBaseWeapon.h"
#include "AttributesComponent.h"

// Sets default values
AMyBaseCharacter::AMyBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the Attributes component
	AttributesComponent = CreateDefaultSubobject<UAttributesComponent>(TEXT("AttributesComponent"));
}

// Called when the game starts or when spawned
void AMyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind to death delegate
	if (AttributesComponent)
	{
		AttributesComponent->OnDeath.AddDynamic(this, &AMyBaseCharacter::HandleDeath);
	}
}

void AMyBaseCharacter::Attack()
{
	if (!AttackMontage || !bCanAttack) return;
	PlayAnimMontage(AttackMontage);
}

// Called every frame
void AMyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyBaseCharacter::GetHit_Implementation(float DamageAmount)
{
	if (AttributesComponent)
	{
		AttributesComponent->TakeDamage(DamageAmount);
	}
}

void AMyBaseCharacter::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s HandleDeath() called"), *GetName());
	if (!DeathMontage) return;
	PlayAnimMontage(DeathMontage);
	// Override this in child classes to implement specific death behavior
}

void AMyBaseCharacter::SetCanAttack(bool bAttack)
{
	bCanAttack = bAttack;
}

// Called to bind functionality to input
void AMyBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyBaseCharacter::SetEquippedWeapon(AMyBaseWeapon* MyBaseWeapon)
{
	EquippedWeapon = MyBaseWeapon;
}

