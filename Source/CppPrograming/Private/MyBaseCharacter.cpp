// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseCharacter.h"

// Sets default values
AMyBaseCharacter::AMyBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyBaseCharacter::Attack()
{
	if (!AttackMontage) return;
	PlayAnimMontage(AttackMontage);
}

// Called every frame
void AMyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

