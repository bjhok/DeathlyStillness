// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/DSCharacter.h"

#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADSCharacter::ADSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	if (SpringArmComp)
	{
		SpringArmComp->SetupAttachment(GetMesh());
		SpringArmComp->SetRelativeRotation(FRotator(0, 0, 90));
		SpringArmComp->TargetArmLength = 300;
	}
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	if (CameraComp)
	{
		CameraComp->SetupAttachment(SpringArmComp);
	}
	GetCharacterMovement()->MaxWalkSpeed = 450;

	AdjunctionComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AdjunctionComp"));
	AdjunctionComp->SetupAttachment(GetMesh());
	// 初始化时间轴组件
	ChangeCameraHeight = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

}


// Called when the game starts or when spawned
void ADSCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (FloatCurve)
	{
		// 绑定浮点型委托到处理函数
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("HandleTimelineUpdate"));
		ChangeCameraHeight->AddInterpFloat(FloatCurve, TimelineProgress);

		// 绑定完成事件委托
		FOnTimelineEvent TimelineFinished;
		TimelineFinished.BindUFunction(this, FName("HandleTimelineFinished"));
		ChangeCameraHeight->SetTimelineFinishedFunc(TimelineFinished);
		
	}


	
	
	UClass* BlueprintVar = StaticLoadClass(ADSAKM::StaticClass(), nullptr,
		TEXT("/Script/Engine.Blueprint'/Game/BluePrints/Weapon/BP_AKM.BP_AKM_C'"));
	if (BlueprintVar != nullptr)
	{  
		FVector SpawnLocation2 = this->GetActorLocation();
		FRotator SpawnRotation2 = this->GetActorRotation();
		AKM = GetWorld()->SpawnActor<ADSAKM>(BlueprintVar,SpawnLocation2,SpawnRotation2);
		AKM->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, NoHaveWeaopn);
	}
}

// Called every frame
void ADSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ADSCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADSCharacter::MoveRight);
	InputComponent->BindAxis("LookUp", this, &ADSCharacter::LookUp);
	InputComponent->BindAxis("LookRight", this, &ADSCharacter::LookRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ADSCharacter::JumpAction);
	InputComponent->BindAction("Walk", IE_Pressed, this, &ADSCharacter::WalkAction);
	InputComponent->BindAction("Run", IE_Pressed, this, &ADSCharacter::RunAction);
	InputComponent->BindAction("Walk", IE_Released, this, &ADSCharacter::JogAction);
	InputComponent->BindAction("Run", IE_Released, this, &ADSCharacter::JogAction);
	InputComponent->BindAction("Crouch", IE_Released, this, &ADSCharacter::CrouchAction);
}

void ADSCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	AdjunctionComp->SetLeaderPoseComponent(GetMesh());
	
	
}

void ADSCharacter::MoveForward(float Value)
{
	FRotator ControlRot = Controller->GetControlRotation();
	FRotator YawRot(0.f, ControlRot.Yaw, 0.f);
	FVector ForwardVector = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardVector, Value);
}

void ADSCharacter::MoveRight(float Value)
{
	FRotator ControlRot = Controller->GetControlRotation();
	FRotator YawRot(0.f, ControlRot.Yaw, 0.f);
	FVector RightVector = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}

void ADSCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ADSCharacter::LookRight(float Value)
{
	AddControllerYawInput(Value);
}

void ADSCharacter::JumpAction()
{
	if (PlayerCanJump)
	{
		PlayerCanJump = false;
		SetJumpAnim();
		Jump();
	}
}

void ADSCharacter::WalkAction()
{
	State = EPlayerState::Walk;
	SetPlayerSpeed();
}

void ADSCharacter::RunAction()
{
	State = EPlayerState::Run;
	SetPlayerSpeed();
}

void ADSCharacter::JogAction()
{
	State = EPlayerState::Jog;
	SetPlayerSpeed();
}

void ADSCharacter::SetPlayerSpeed()
{
	switch (State)
	{
		case EPlayerState::Walk:
			GetCharacterMovement()->MaxWalkSpeed = 150;
			GetCharacterMovement()->JumpZVelocity = 320;
			break;
		case EPlayerState::Jog:
			GetCharacterMovement()->MaxWalkSpeed = 450;
			GetCharacterMovement()->JumpZVelocity = 360;
			break;
		case EPlayerState::Run:
			GetCharacterMovement()->MaxWalkSpeed = 550;
			GetCharacterMovement()->JumpZVelocity = 400;
			break;
	}
}

void ADSCharacter::CrouchAction()
{
	if (PlayerCanCrouch)
	{
		ChangeCameraHeight->PlayFromStart();
		SetCrouchVal(PlayerCanCrouch);
		Crouch();

		PlayerCanCrouch = false;
	}
	else
	{
		ChangeCameraHeight->Reverse();
		SetCrouchVal(PlayerCanCrouch);
		UnCrouch();

		PlayerCanCrouch = true;
	}
}

void ADSCharacter::HandleTimelineUpdate(float OutputValue)
{
	SpringArmComp->SocketOffset = FVector(SpringArmComp->SocketOffset.X,
										  SpringArmComp->SocketOffset.Y,
										  OutputValue);
}

