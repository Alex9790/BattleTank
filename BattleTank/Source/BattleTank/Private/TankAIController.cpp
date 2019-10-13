// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("ATankAIController BeginPlay"));

    //identifica el tanque que este AI Controller esta controlando
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("ATankAIController No posee tanque."));
    }else{
        UE_LOG(LogTemp, Warning, TEXT("ATankAIController Tank Id = %s."), *ControlledTank->GetName());   
    }

    //identifica el tanque que controla el jugador en el mundo
    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Error, TEXT("ATankAIController No encuentra jugador."));
    }else{
        UE_LOG(LogTemp, Warning, TEXT("ATankAIController Jugador encontrado = %s."), *PlayerTank->GetName());   
    }
    
}

ATank* ATankAIController::GetPlayerTank() const{
    //se hace de esta forma porque castear null como ATank generara una exception
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(!PlayerPawn){
        return nullptr;
    }
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

ATank* ATankAIController::GetControlledTank() const{
    return Cast<ATank>(GetPawn()); //retorna el Pawn que el cntrolador esta actualmente poseyendo y se castea como un Tanque
    
}