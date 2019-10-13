// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay(){
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("TankPlayerController BeginPlay"));

    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("TankPlayerController No posee tanque."));
    }else{
        UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Tank Id = %s."), *ControlledTank->GetName());   
    }
    
}

void ATankPlayerController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Ticking."));

}

ATank* ATankPlayerController::GetControlledTank() const{
    return Cast<ATank>(GetPawn()); //retorna el Pawn que el cntrolador esta actualmente poseyendo y se castea como un Tanque
    
}

void ATankPlayerController::AimTowardsCrosshair(){
    
}