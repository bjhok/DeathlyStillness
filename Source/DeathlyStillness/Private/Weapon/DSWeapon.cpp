// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DSWeapon.h"

// Sets default values
ADSWeapon::ADSWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ADSWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADSWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

