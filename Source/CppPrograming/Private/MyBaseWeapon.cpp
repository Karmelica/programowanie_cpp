// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseWeapon.h"

#include "MyBaseCharacter.h"

void AMyBaseWeapon::Interact_Implementation(AActor* OuterActor)
{
	Super::Interact_Implementation(OuterActor);
	Equip(OuterActor);
}

void AMyBaseWeapon::AttachToSocket(USceneComponent* InParent, FName& InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	TransformRules.ScaleRule = EAttachmentRule::KeepWorld;
	RootComponent->AttachToComponent(InParent, TransformRules, InSocketName);
}

void AMyBaseWeapon::Equip(AActor* OuterActor)
{
	if (AMyBaseCharacter* Character = Cast<AMyBaseCharacter>(OuterActor))
	{
		AttachToSocket(Character->GetMesh(), MainSocketName);
		Character->SetEquippedWeapon(this);
	}
}
