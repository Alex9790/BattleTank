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

    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const{
    return Cast<ATank>(GetPawn()); //retorna el Pawn que el controlador esta actualmente poseyendo y se castea como un Tanque
}

void ATankPlayerController::AimTowardsCrosshair(){
    //no tiene sentido apuntar a la pantalla si no tienes control sobre un tanque
    if(!GetControlledTank()){
        return;
    }

    FVector HitLocation;    //Out Parameter
    //UE_LOG(LogTemp, Warning, TEXT("HitLocation = %s."), *HitLocation.ToString()); 

    //se realiza un raytrace
    if(GetSightRayHitLocation(HitLocation)){    
        UE_LOG(LogTemp, Warning, TEXT("HitLocation = %s."), *HitLocation.ToString()); 
    }

    //Obtener la posicion mundo obtenido por el LineTrace a traves del Crosshair
    //si intercepta el Landscape
        //decirle al Tank que se controla que apunte en esta direccion
}

//Obtener la posicion mundo obtenido por el LineTrace a traves del Crosshair, true si coliciona con el Landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {

    HitLocation = FVector(1.0);
    return true;
    /*if ()
    {
        return true;
    }
    return false;*/
}