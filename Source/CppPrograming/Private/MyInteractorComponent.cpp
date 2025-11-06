// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInteractorComponent.h"

#include "Engine/StaticMeshSocket.h"

// Sets default values for this component's properties
UMyInteractorComponent::UMyInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TargetSocket = CreateDefaultSubobject<UStaticMeshSocket>(TEXT("TargetSocket"));
	TargetSocket->SocketName = TEXT("MySocket");

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


