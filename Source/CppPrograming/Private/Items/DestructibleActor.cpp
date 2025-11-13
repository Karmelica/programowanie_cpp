// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/DestructibleActor.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ADestructibleActor::ADestructibleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	ObjectMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADestructibleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADestructibleActor::GetHit_Implementation(float Damage)
{
	Bonk();
}

void ADestructibleActor::Bonk()
{
	HitPoints--;
	if (HitPoints <= 0)
	{
		Destroy();
	}
}


// Called every frame
void ADestructibleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

