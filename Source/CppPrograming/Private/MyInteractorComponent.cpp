// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInteractorComponent.h"

#include "MyPlayerCharacter.h"
#include "PlayerInterface.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UMyInteractorComponent::UMyInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyInteractorComponent::TryInteract()
{
	FHitResult SphereHit;
	SphereTrace(SphereHit);

	AActor* HitActor = SphereHit.GetActor();
	if (!HitActor) return;
	if (HitActor->Implements<UInteractableInterface>())
	{
		IInteractableInterface::Execute_Interact(HitActor, GetOwner());
		IgnoreActors.Add(HitActor);
	}
}

void UMyInteractorComponent::SphereTrace(FHitResult& SphereHit)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	for (AActor* Actor : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actor);
	}
	AMyPlayerCharacter* CppOwner = Cast<AMyPlayerCharacter>(GetOwner());

	FVector EndTrace = CppOwner->GetCameraLocation() + (CppOwner->GetCameraForwardVector() * 500.f);

	/*SphereTraceSingle(
		 const UObject * WorldContextObject,
		 const FVector Start,
		 const FVector End,
		 float Radius,
		 ETraceTypeQuery TraceChannel,
		 bool bTraceComplex,
		 const TArray<AActor*>&ActorsToIgnore,
		 EDrawDebugTrace::Type DrawDebugType,
		 FHitResult & OutHit,
		 bool bIgnoreSelf,
		 FLinearColor TraceColor,
		 FLinearColor TraceHitColor,
		 float DrawTime)
	 */

	UKismetSystemLibrary::SphereTraceSingle(
		this,
		CppOwner->GetCameraLocation(),
		EndTrace,
		TraceSphereRadius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		true,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		SphereHit,
		true
	);
}


