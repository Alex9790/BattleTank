// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("ATankAIController BeginPlay"));

    //identifica el tanque que este AI Controller esta controlando
    ControlledTank = Cast<ATank>(GetPawn());
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("ATankAIController No posee tanque."));
    }else{
        UE_LOG(LogTemp, Warning, TEXT("ATankAIController Tank Id = %s."), *ControlledTank->GetName());   
    }

    //identifica el tanque que controla el jugador en el mundo
    PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Error, TEXT("ATankAIController No encuentra jugador."));
    }else{
        UE_LOG(LogTemp, Warning, TEXT("ATankAIController Jugador encontrado = %s."), *PlayerTank->GetName());   
    }
    
}

void ATankAIController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
    
    //auto ControlledTank = Cast<ATank>(GetPawn()); //retorna el Pawn que el cntrolador esta actualmente poseyendo y se castea como un Tanque
    
    //no tiene sentido apuntar a la pantalla si no tienes control sobre un tanque
    if(!ControlledTank){
        return;
    }

    //apuntar al tanque del jugador
    ControlledTank->AimAt(PlayerTank->GetActorLocation());

    //disparar al juador
    ControlledTank->Fire();
}