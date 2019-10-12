// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const{
    return Cast<ATank>(GetPawn()); //retorna el Pawn que el cntrolador esta actualmente poseyendo y se castea como un Tanque

}

