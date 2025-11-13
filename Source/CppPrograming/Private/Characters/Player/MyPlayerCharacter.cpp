// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/MyPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/Player/MyInteractorComponent.h"


AMyPlayerCharacter::AMyPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 150.f;
	CameraBoom->bUsePawnControlRotation = true;
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ViewCamera->bUsePawnControlRotation = false;
	InteractorComponent = CreateDefaultSubobject<UMyInteractorComponent>(TEXT("InteractorComponent"));

}

void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerCharacter::Move(const FInputActionValue& InputActionValue)
{
	FVector2D MoveValue = InputActionValue.Get<FVector2D>();

	if (Controller)
	{
		if (MoveValue.X != 0)
		{
			const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, MoveValue.X);
		}
		if (MoveValue.Y != 0)
		{
			const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, MoveValue.Y);
		}
	}
}

void AMyPlayerCharacter::Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookValue = InputActionValue.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookValue.X);
		AddControllerPitchInput(-LookValue.Y);
	}
}

void AMyPlayerCharacter::PlayerInteract()
{
	InteractorComponent->TryInteract();
}

void AMyPlayerCharacter::Attack()
{
	Super::Attack();
}

FVector AMyPlayerCharacter::GetCameraLocation()
{
	return ViewCamera->GetComponentLocation();
}

FVector AMyPlayerCharacter::GetCameraForwardVector()
{
	return ViewCamera->GetForwardVector();
}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* Player = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		Input->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyPlayerCharacter::PlayerInteract);
		Input->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyPlayerCharacter::Attack);

	}
}
