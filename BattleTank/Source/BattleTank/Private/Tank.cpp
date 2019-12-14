// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//log para identificar cuando se crea el Tank
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Constructor - TankName = %s"), *TankName)
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	//UE_LOG(LogTemp, Warning, TEXT("DamageAmount=%f - DamagePoints=%i - DamageToApply=%i"), DamageAmount, DamagePoints, DamageToApply)

	CurrentHealth -= DamageToApply;
	if(CurrentHealth <= 0){
		//UE_LOG(LogTemp, Warning, TEXT("Tank's Dead"))
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay - TankName = %s"), *TankName)
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
