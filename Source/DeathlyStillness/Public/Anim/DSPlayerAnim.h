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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInTheAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsJump;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCrouch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Yaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Pitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHoldGun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsEquipWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EquipWeaponDir;
};
