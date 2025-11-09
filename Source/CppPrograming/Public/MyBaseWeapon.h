// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyItem.h"
#include "MyBaseWeapon.generated.h"

UCLASS()
class CPPPROGRAMING_API AMyBaseWeapon : public AMyItem
{
	GENERATED_BODY()

protected:

	void AttachToSocket(USceneComponent* InParent, FName& InSocketName);
	void Equip(AActor* OuterActor);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	FName MainSocketName = FName("hand_RSocket");

	virtual void Interact_Implementation(AActor* OuterActor) override;
};
