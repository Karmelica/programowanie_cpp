// Fill out your copyright notice in the Description page of Project Settings.

#include "Animations/EnableAttack.h"
#include "Characters/MyBaseCharacter.h"
#include "Items/MyBaseWeapon.h"

void UEnableAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                           const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp) return;

	// Pobierz w≥aúciciela SkeletalMeshComponent (powinien to byÊ Character)
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	// Sprawdü czy w≥aúciciel to AMyBaseCharacter
	AMyBaseCharacter* Character = Cast<AMyBaseCharacter>(Owner);
	if (!Character) return;

	Character->SetCanAttack(true);

	// Pobierz ekwipowanπ broÒ
	AMyBaseWeapon* Weapon = Character->EquippedWeapon;
	if (!Weapon) return;

	// WyczyúÊ listÍ trafionych aktorÛw i w≥πcz hitbox
	Weapon->ClearHitActors();
	Weapon->EnableHitbox();
	//UE_LOG(LogTemp, Warning, TEXT("EnableHitbox Notify - Hitbox enabled for %s"), *Character->GetName());
}
