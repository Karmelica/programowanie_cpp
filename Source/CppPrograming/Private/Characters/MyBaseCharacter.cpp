#include "Characters/MyBaseCharacter.h"
#include "Characters/Player/AttributesComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enums/EPawnState.h"
#include "Items/MyBaseWeapon.h"

// Sets default values
AMyBaseCharacter::AMyBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the Attributes component
	AttributesComponent = CreateDefaultSubobject<UAttributesComponent>(TEXT("AttributesComponent"));
	CurrentState = EPawnState::Patrol;
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
	if (!AttackMontage || !bCanAttack || !EquippedWeapon || CurrentState == EPawnState::Hit) return;
	PlayAnimMontage(AttackMontage);
}

void AMyBaseCharacter::Jump()
{
	Super::Jump();
}

// Called every frame
void AMyBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

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
	if (!AttackMontage) return;
	StopAnimMontage(AttackMontage);
}

void AMyBaseCharacter::DamageTaken()
{
	LastState = CurrentState;
	CurrentState = EPawnState::Hit;
	bCanAttack = false;
	if (!EquippedWeapon) return;
	SetWeaponHitbox(false);
	//UE_LOG(LogTemp, Warning, TEXT("%s DamageTaken() called"), *GetName());
}

void AMyBaseCharacter::DamageTakenEnd()
{
	CurrentState = LastState;
	bCanAttack = true;
	//UE_LOG(LogTemp, Warning, TEXT("%s DamageTakenEnd() called"), *GetName());
}

void AMyBaseCharacter::HandleDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s HandleDeath() called"), *GetName());
	CurrentState = EPawnState::Dead;
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

void AMyBaseCharacter::SetWeaponHitbox(bool bActive)
{
	AMyBaseWeapon* Weapon = EquippedWeapon;
	if (!Weapon) return;

	if (bActive){
		Weapon->ClearHitActors();
		Weapon->EnableHitbox();
	}
	else{
		Weapon->DisableHitbox();
	}
}

void AMyBaseCharacter::Die()
{
	StopAnimMontage(DeathMontage);
	//UE_LOG(LogTemp, Warning, TEXT("%s Die() called - destroying actor"), *GetName());
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


