// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DSPlayerAnim.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DEATHLYSTILLNESS_API UDSPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDSPlayerAnim();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

};
