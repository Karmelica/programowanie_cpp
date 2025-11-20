// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/MyBaseWeapon.h"
#include "Characters/MyBaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void AMyBaseWeapon::Interact_Implementation(AActor* OuterActor)
{
	Super::Interact_Implementation(OuterActor);
	Equip(OuterActor);
}

void AMyBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	DisableHitbox();
	if (AMyBaseCharacter* MyOwner = Cast<AMyBaseCharacter>(GetOwner()))
	{
		MyOwner->SetEquippedWeapon(this);
	}
}

void AMyBaseWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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

	bShouldTrace = false;
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
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AMyBaseWeapon::EnableHitbox()
{
	if (!SwordHitbox) return;
	//UE_LOG(LogTemp, Warning, TEXT("Weapon Hitbox ENABLED"));
	SwordHitbox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SwordHitbox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	bShouldTrace = true;
}

void AMyBaseWeapon::DisableHitbox()
{
	if (!SwordHitbox) return;
	//UE_LOG(LogTemp, Warning, TEXT("Weapon Hitbox DISABLED"));
	SwordHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bShouldTrace = false;
}

void AMyBaseWeapon::BoxTrace(FHitResult& OutHit)
{
	if (!TraceStart || !TraceEnd || !SwordHitbox) return;

	const FVector Start = TraceStart->GetComponentLocation();
	const FVector End = TraceEnd->GetComponentLocation();
	
	// Pobierz wymiary box collider z SwordHitbox
	FVector BoxExtent = SwordHitbox->GetScaledBoxExtent()/1.8f;

	// Pobierz rotacjê z SwordHitbox (zamiast z TraceStart)
	const FRotator BoxRotation = SwordHitbox->GetComponentRotation();
	
	// Ustawienie kana³ów kolizji do ignorowania
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetOwner());
	
	// Dodaj wszystkich ju¿ trafionych aktorów do ignorowania
	ActorsToIgnore.Append(HitActors);

	// Wykonanie box trace z wymiarami SwordHitbox
	const bool bHit = UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		BoxExtent,
		BoxRotation,
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

		AActor* HitActor = HitResult.GetActor();
		if (!HitActor) return;
		if (HitActor->Implements<UCombatInterface>())
		{
			ICombatInterface::Execute_GetHit(HitActor, 20.f);
		}

		/*if (bShowDebugTrace)
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
		}*/
	}
}

void AMyBaseWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (AActor* HitActor = Cast<AActor>(OtherActor))
	{
		if (!bShouldTrace || HitActor == GetOwner()) return;
		DisableHitbox();
		PerformBoxTrace();
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
