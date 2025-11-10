// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseWeapon.h"

#include "MyBaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

void AMyBaseWeapon::Interact_Implementation(AActor* OuterActor)
{
	Super::Interact_Implementation(OuterActor);
	Equip(OuterActor);
}

AMyBaseWeapon::AMyBaseWeapon()
{
	SwordHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordHitbox"));
	SwordHitbox->SetupAttachment(RootComponent);

	// Tworzenie punktów œledzenia
	TraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("TraceStart"));
	TraceStart->SetupAttachment(RootComponent);

	TraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("TraceEnd"));
	TraceEnd->SetupAttachment(RootComponent);
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

void AMyBaseWeapon::BoxTrace(FHitResult& OutHit)
{
	if (!TraceStart || !TraceEnd) return;

	const FVector Start = TraceStart->GetComponentLocation();
	const FVector End = TraceEnd->GetComponentLocation();
	
	// Ustawienie kana³ów kolizji do ignorowania
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetOwner());
	
	// Dodaj wszystkich ju¿ trafionych aktorów do ignorowania
	ActorsToIgnore.Append(HitActors);

	// Wykonanie box trace
	const bool bHit = UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		BoxTraceExtent,
		TraceStart->GetComponentRotation(),
		UEngineTypes::ConvertToTraceType(ECC_Pawn),
		false,
		ActorsToIgnore,
		bShowDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		OutHit,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		2.0f
	);

	if (bHit && OutHit.GetActor())
	{
		// Dodaj trafionego aktora do listy
		HitActors.AddUnique(OutHit.GetActor());
		OnHit(OutHit);
	}
}

void AMyBaseWeapon::OnHit(const FHitResult& HitResult)
{
	// Logowanie miejsca zderzenia
	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon hit: %s at location: %s"), 
			*HitResult.GetActor()->GetName(), 
			*HitResult.ImpactPoint.ToString());

		// Opcjonalne: rysowanie punktu trafienia
		if (bShowDebugTrace)
		{
			DrawDebugSphere(
				GetWorld(),
				HitResult.ImpactPoint,
				10.0f,
				12,
				FColor::Orange,
				false,
				3.0f
			);
		}

		// Tutaj mo¿esz dodaæ logikê zadawania obra¿eñ
		// np. wywo³anie funkcji TakeDamage na trafionym aktorze
		if (AMyBaseCharacter* HitCharacter = Cast<AMyBaseCharacter>(HitResult.GetActor()))
		{
			HitCharacter->GetHit_Implementation(20.f); // Przyk³adowa wartoœæ obra¿eñ
			UE_LOG(LogTemp, Warning, TEXT("Hit character: %s"), *HitCharacter->GetName());
		}


	}
}

void AMyBaseWeapon::PerformBoxTrace()
{
	FHitResult HitResult;
	BoxTrace(HitResult);
}

void AMyBaseWeapon::ClearHitActors()
{
	HitActors.Empty();
}
