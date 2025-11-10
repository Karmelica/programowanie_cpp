// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyItem.h"
#include "MyBaseWeapon.generated.h"

class UBoxComponent;

UCLASS()
class CPPPROGRAMING_API AMyBaseWeapon : public AMyItem
{
	GENERATED_BODY()

protected:
	AMyBaseWeapon();

	void AttachToSocket(USceneComponent* InParent, FName& InSocketName);
	void Equip(AActor* OuterActor);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	FName MainSocketName = FName("hand_RSocket");

	UPROPERTY(EditAnywhere)
	UBoxComponent* SwordHitbox;

	virtual void Interact_Implementation(AActor* OuterActor) override;

	// Funkcje do zarz¹dzania hitboxem broni
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EnableHitbox();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void DisableHitbox();
};
