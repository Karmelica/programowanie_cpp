// Fill out your copyright notice in the Description page of Project Settings.


#include "DisableAttack.h"
#include "MyBaseCharacter.h"
#include "MyBaseWeapon.h"

void UDisableAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
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

	Character->SetCanAttack(false);

	// Pobierz ekwipowanπ broÒ
	AMyBaseWeapon* Weapon = Character->EquippedWeapon;
	if (!Weapon) return;

	// Wy≥πcz hitbox broni
	Weapon->DisableHitbox();
	//UE_LOG(LogTemp, Warning, TEXT("DisableHitbox Notify - Hitbox disabled for %s"), *Character->GetName());
}
