// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Characters/MyBaseCharacter.h"
#include "MyPlayerCharacter.generated.h"

class UMyInteractorComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class CPPPROGRAMING_API AMyPlayerCharacter : public AMyBaseCharacter
{
	GENERATED_BODY()


private:

	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere)
	UCameraComponent* ViewCamera;
	UPROPERTY(EditAnywhere)
	UMyInteractorComponent* InteractorComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	float JumpCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SprintAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float SprintCost;

	bool bIsSprinting = false;

protected:

	AMyPlayerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void SetSprinting();

	virtual void Jump() override;
	virtual void Attack() override;
	void Interact();

public:
	UFUNCTION(BlueprintCallable)
	bool GetSprinting() const { return bIsSprinting; }
	UMyInteractorComponent* GetInteractorComponent() const { return InteractorComponent; }
	FVector GetCameraLocation();
	FVector GetCameraForwardVector();
};
