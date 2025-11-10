// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseWeapon.h"

#include "MyBaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

void AMyBaseWeapon::Interact_Implementation(AActor* OuterActor)
{
	Super::Interact_Implementation(OuterActor);
	Equip(OuterActor);
}

AMyBaseWeapon::AMyBaseWeapon()
{
	SwordHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordHitbox"));
	SwordHitbox->SetupAttachment(RootComponent);
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
		// Wy³¹cz hitbox po ekwipowaniu (domyœlnie)
		DisableHitbox();
	}
}

void AMyBaseWeapon::EnableHitbox()
{
	if (!SwordHitbox) return;
	//UE_LOG(LogTemp, Warning, TEXT("Weapon Hitbox ENABLED"));
	SwordHitbox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SwordHitbox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AMyBaseWeapon::DisableHitbox()
{
	if (!SwordHitbox) return;
	//UE_LOG(LogTemp, Warning, TEXT("Weapon Hitbox DISABLED"));
	SwordHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
