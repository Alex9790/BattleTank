// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();      
}

void ATankAIController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
    
    //identifica el tanque que controla el jugador en el mundo
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    //identifica el tanque que este AI Controller esta controlando
	auto ControlledTank = GetPawn();

	if (ensure(PlayerTank)){        
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

		// Aim towards the player
        auto ControlledTankComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		ControlledTankComponent->AimAt(PlayerTank->GetActorLocation());

		if (ControlledTankComponent->GetFiringState() == EFiringState::Locked) {
			ControlledTankComponent->Fire();
		}
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//se subscribe al evento del Tank OnDeath()
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank's Dead"))
	if (!ensure(GetPawn())) { return; }	//TODO: remover ensure cuando sepamos que esta bien
	GetPawn()->DetachFromControllerPendingDestroy();
}
