// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DisableHitbox.generated.h"

/**
 * 
 */
UCLASS()
class CPPPROGRAMING_API UDisableHitbox : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
