// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
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
    
    //buscando componente TankAimingComponent
    auto AutoComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
    if(AutoComponent){
        FoundAimingComponent(AutoComponent);
    }else{
        UE_LOG(LogTemp, Warning, TEXT("TankPlayerController No puede conseguir TankAimingComponent."));
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
        //UE_LOG(LogTemp, Warning, TEXT("HitLocation = %s."), *HitLocation.ToString()); 
        //se envia al tanque que se esta controlando la ubicacion hacia donde apuntar
        GetControlledTank()->AimAt(HitLocation);
    }

    //Obtener la posicion mundo obtenido por el LineTrace a traves del Crosshair
    //si intercepta el Landscape
        //decirle al Tank que se controla que apunte en esta direccion
}

//Obtener la posicion mundo obtenido por el LineTrace a traves del Crosshair, true si coliciona con el Landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {

    //Encontrar la posicion del crosshair, en coordenadas de pixel
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);    //obteniendo la ubicacion del crosshair en pantalla
    //UE_LOG(LogTemp, Warning, TEXT("ScreenLocation = %s."), *ScreenLocation.ToString()); 
    
    //"De-Project" la posicion de pantalla del crosshair a una direccion hacia el mundo
    FVector CameraWorldLocation, LookDirection;
    if(GetLookDirection(ScreenLocation, CameraWorldLocation, LookDirection)){
        //UE_LOG(LogTemp, Warning, TEXT("WorldLocation = %s."), *CameraWorldLocation.ToString());
        //UE_LOG(LogTemp, Warning, TEXT("WorldDirection = %s."), *LookDirection.ToString());

        //se realiza LineTrace a traves de esa direccion, y identificar contra que coliciona, dentro del rango definido
        GetLookVectorHitLocation(LookDirection, HitLocation);
        
    }   

    return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    //UE_LOG(LogTemp, Warning, TEXT("StartLocation = %s."), *StartLocation.ToString());
    /*LineTraceSingleByChannel
    (
        struct FHitResult & OutHit,                         //Primer objeto con el que colisiona
        const FVector & Start,                              //inicio de la ubicacion del rayo
        const FVector & End,                                //fin de la ubicacion del rayo
        ECollisionChannel TraceChannel,                     //El "channel" en el que sta el objeto, usado para determinar cual componente detectar
        const FCollisionQueryParams & Params,               //parametros adicionales
        const FCollisionResponseParams & ResponseParam      //ResponseContainer a ser usado
    )*/
    if (GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility       //colisionara con todo lo que se vea
    ))
    {
        HitLocation = HitResult.Location;   //se obtiene del FHitResult la ubicacion en mundo donde ocurrio la colision
        return true;
    }
    HitLocation = FVector(0);
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& CameraWorldLocation, FVector& LookDirection) const{
    return DeprojectScreenPositionToWorld( ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}