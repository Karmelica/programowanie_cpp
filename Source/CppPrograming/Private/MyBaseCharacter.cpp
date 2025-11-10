// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseCharacter.h"
#include "MyBaseWeapon.h"
#include "AttributesComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	
	if (!DeathMontage) 
	{
		// Jeœli nie ma animacji œmierci, od razu zniszcz postaæ
		Destroy();
		return;
	}

	// Wy³¹cz input
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		DisableInput(PC);
		UE_LOG(LogTemp, Warning, TEXT("Input disabled for %s"), *GetName());
	}

	// Zatrzymaj ruch postaci
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->StopMovementImmediately();

	// Wy³¹cz kolizjê z postaciami
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	
	// Zagraj animacjê œmierci
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		// Podepnij callback do zakoñczenia monta¿u
		FOnMontageEnded MontageEndDelegate;
		MontageEndDelegate.BindUObject(this, &AMyBaseCharacter::OnDeathMontageEnded);
		AnimInstance->Montage_SetEndDelegate(MontageEndDelegate, DeathMontage);
		
		// Odtwórz monta¿ œmierci
		PlayAnimMontage(DeathMontage);
	}
	else
	{
		// Jeœli nie ma AnimInstance, od razu zniszcz
		Destroy();
	}
}

void AMyBaseCharacter::OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Death montage ended, destroying actor"), *GetName());
	
	// Zniszcz postaæ po zakoñczeniu animacji
	Destroy();
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

