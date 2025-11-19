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
private:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	AMyBaseWeapon();


	bool bShouldTrace;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	USceneComponent* TraceStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	USceneComponent* TraceEnd;

	UPROPERTY()
	TArray<AActor*> HitActors;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	FName MainSocketName = FName("hand_RSocket");

	UPROPERTY(EditAnywhere)
	UBoxComponent* SwordHitbox;

	// Czy pokazywaæ debug trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bShowDebugTrace = false;

protected:

	void AttachToSocket(USceneComponent* InParent, FName& InSocketName);
	void Equip(AActor* OuterActor);

	// Funkcja wykonuj¹ca box trace
	void BoxTrace(FHitResult& OutHit);

	// Funkcja wywo³ywana przy trafieniu
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void OnHit(const FHitResult& HitResult);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:

	virtual void Interact_Implementation(AActor* OuterActor) override;

	// Funkcje do zarz¹dzania hitboxem broni
	UFUNCTION()
	void EnableHitbox();

	UFUNCTION()
	void DisableHitbox();

	// Wywo³ywane co klatkê podczas ataku
	UFUNCTION()
	void PerformBoxTrace();

	// Czyœci listê trafionych aktorów (wywo³aj na pocz¹tku nowego ataku)
	UFUNCTION()
	void ClearHitActors();
};
