// Fill out your copyright notice in the Description page of Project Settings.


#include "EnableHitbox.h"
#include "MyBaseCharacter.h"
#include "MyBaseWeapon.h"

void UEnableHitbox::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
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
	
	// Pobierz ekwipowanπ broÒ
	AMyBaseWeapon* Weapon = Character->EquippedWeapon;
	if (!Weapon) return;
	
	// W≥πcz hitbox broni
	Weapon->EnableHitbox();
	UE_LOG(LogTemp, Warning, TEXT("EnableHitbox Notify - Hitbox enabled for %s"), *Character->GetName());
}
