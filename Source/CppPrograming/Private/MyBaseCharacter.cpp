// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseCharacter.h"
#include "MyBaseWeapon.h"
#include "AttributesComponent.h"
#include "Components/CapsuleComponent.h"

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
		AttributesComponent->OnTakeDamage.AddDynamic(this, &AMyBaseCharacter::GetHitAnim);
	}
}

void AMyBaseCharacter::Attack()
{
	if (!AttackMontage || !bCanAttack || !EquippedWeapon) return;
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

void AMyBaseCharacter::GetHitAnim()
{
	if (!TakeDamageMontage) return;
	PlayAnimMontage(TakeDamageMontage);
}

void AMyBaseCharacter::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s HandleDeath() called"), *GetName());
	if (!DeathMontage) return;
	PlayAnimMontage(DeathMontage);
	if (UCapsuleComponent* capsule = GetCapsuleComponent())
	{
		capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AMyBaseCharacter::SetCanAttack(bool bAttack)
{
	bCanAttack = bAttack;
}

void AMyBaseCharacter::Die()
{
	StopAnimMontage(DeathMontage);
	UE_LOG(LogTemp, Warning, TEXT("%s Die() called - destroying actor"), *GetName());
	Destroy();
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

