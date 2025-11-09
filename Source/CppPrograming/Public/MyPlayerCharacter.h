// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "MyBaseCharacter.h"
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

protected:
	AMyPlayerCharacter();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void PlayerInteract();
	virtual void Attack() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* InteractAction;

private:

	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere)
	UCameraComponent* ViewCamera;
	UPROPERTY(EditAnywhere)
	UMyInteractorComponent* InteractorComponent;

public:
	UMyInteractorComponent* GetInteractorComponent() const { return InteractorComponent; }
	FVector GetCameraLocation();
	FVector GetCameraForwardVector();
};
