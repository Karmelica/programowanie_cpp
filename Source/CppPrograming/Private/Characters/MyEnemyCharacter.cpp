// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyEnemyCharacter.h"
#include "Perception/PawnSensingComponent.h"


AMyEnemyCharacter::AMyEnemyCharacter()
{
	AIComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("AIComponent"));
}


