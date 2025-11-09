// Fill out your copyright notice in the Description page of Project Settings.

	
#include "MyItem.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AMyItem::AMyItem()
{


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Utwórz ItemMesh i ustaw jako Root Component
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;
	
	// KONFIGURACJA KOLIZJI DLA ITEMESH - TO JEST KLUCZOWE!
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	// Utwórz SkeletalMesh i pod³¹cz do Root Component
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	// Wy³¹cz kolizjê dla SkeletalMesh (nie potrzebna, ItemMesh wystarczy)
	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Utwórz Capsule i pod³¹cz do Root Component
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(RootComponent);
	// Wy³¹cz kolizjê dla Capsule (lub zostaw w³¹czon¹ jeœli potrzebujesz)
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AMyItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyItem::Interact_Implementation(AActor* OuterActor)
{
	IInteractableInterface::Interact_Implementation(OuterActor);
	//ItemMesh->SetSimulatePhysics(false);
	SetOwner(OuterActor);
}


