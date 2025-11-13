// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/SetWeaponHitbox.h"
#include "Characters/MyBaseCharacter.h"
#include "Items/MyBaseWeapon.h"

void USetWeaponHitbox::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

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

	// WyczyúÊ listÍ trafionych aktorÛw przed rozpoczÍciem nowego ataku
	Weapon->ClearHitActors();
	
	// W≥πcz hitbox broni
	Weapon->EnableHitbox();
	//UE_LOG(LogTemp, Warning, TEXT("SetWeaponHitbox Notify - Hitbox enabled and hit actors cleared for %s"), *Character->GetName());
}

void USetWeaponHitbox::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

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

	// Wy≥πcz hitbox broni
	Weapon->DisableHitbox();
	//UE_LOG(LogTemp, Warning, TEXT("SetWeaponHitbox Notify - Hitbox disabled for %s"), *Character->GetName());
}

void USetWeaponHitbox::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

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

	// Wykonuj box trace co klatkÍ podczas trwania animacji ataku
	Weapon->PerformBoxTrace();
}
