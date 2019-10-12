// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("ATankAIController BeginPlay"));

    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("ATankAIController No posee tanque."));
    }else{
        UE_LOG(LogTemp, Warning, TEXT("ATankAIController Tank Id = %s."), *ControlledTank->GetName());   
    }
    
}

ATank* ATankAIController::GetControlledTank() const{
    return Cast<ATank>(GetPawn()); //retorna el Pawn que el cntrolador esta actualmente poseyendo y se castea como un Tanque
    
}