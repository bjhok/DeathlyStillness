// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h" 
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Universal/AllStruct.h"
#include "Weapon/DSAKM.h"
#include "DSCharacter.generated.h"



UCLASS()
class DEATHLYSTILLNESS_API ADSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 重写构造脚本
	virtual void OnConstruction(const FTransform& Transform) override;
	
	//键盘输入事件对应的函数
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void LookRight(float Value);
	void JumpAction();
	void WalkAction();
	void RunAction();
	void JogAction();
	//根据状态设置玩家速度
	void SetPlayerSpeed();
	//根据状态设置跳跃动画
	UFUNCTION(BlueprintImplementableEvent, Category = "SetJumpAnim")
	void SetJumpAnim();
	void CrouchAction();
	//给动画蓝图蹲伏bool赋值
	UFUNCTION(BlueprintImplementableEvent, Category = "SetCrouchVal")
	void SetCrouchVal(bool CanCrouch);
	// // 时间轴更新时调用
	UFUNCTION()
	void HandleTimelineUpdate(float OutputValue); 
public:	
	UPROPERTY(Category = "character",VisibleAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;
	UPROPERTY(Category = "character",VisibleAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp;

	UPROPERTY(Category = "character",VisibleAnywhere,BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* AdjunctionComp;
	
	UPROPERTY(Category = "character",VisibleAnywhere,BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	FName NoHaveWeaopn = "NoWeapon";
	UPROPERTY(Category = "character",VisibleAnywhere,BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	FName HaveWeaopn = "HaveWeapon";

	UPROPERTY(BlueprintReadWrite, Category = "character", meta = (AllowPrivateAccess = "true"))
	ADSAKM* AKM;
	
	UPROPERTY(Category = "character",VisibleAnywhere,BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	EPlayerState State = EPlayerState::Jog;

	UPROPERTY(BlueprintReadWrite, Category = "character", meta = (AllowPrivateAccess = "true"))
	bool PlayerCanJump = true;
	UPROPERTY(BlueprintReadWrite, Category = "character", meta = (AllowPrivateAccess = "true"))
	bool PlayerCanCrouch = true;
	
	// 声明时间轴组件-蹲下
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timeline")
	UTimelineComponent* ChangeCameraHeight;

	// 声明浮点曲线引用-蹲下
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
	UCurveFloat* FloatCurve;

};
