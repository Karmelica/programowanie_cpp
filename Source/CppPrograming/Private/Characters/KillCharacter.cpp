// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/KillCharacter.h"
#include "Characters/MyBaseCharacter.h"

void UKillCharacter::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                            const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp) return;
	// Pobierz w³aœciciela SkeletalMeshComponent (powinien to byæ Character)
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;
	AMyBaseCharacter* Character = Cast<AMyBaseCharacter>(Owner);
	if (!Character) return;
	Character->Die();
}
