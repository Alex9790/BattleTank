// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("ATankAIController BeginPlay"));

    //identifica el tanque que este AI Controller esta controlando
    ControlledTank = Cast<ATank>(GetPawn());
    if (!ensure(ControlledTank))
    {
        UE_LOG(LogTemp, Error, TEXT("ATankAIController No posee tanque."));
    }else{
        UE_LOG(LogTemp, Warning, TEXT("ATankAIController Tank Id = %s."), *ControlledTank->GetName());   
    }

    //identifica el tanque que controla el jugador en el mundo
    PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (!ensure(PlayerTank))
    {
        UE_LOG(LogTemp, Error, TEXT("ATankAIController No encuentra jugador."));
    }else{
        UE_LOG(LogTemp, Warning, TEXT("ATankAIController Jugador encontrado = %s."), *PlayerTank->GetName());   
    }
    
}

void ATankAIController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
    
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (ensure(PlayerTank)){        
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire(); // TODO limit firing rate
	}
}