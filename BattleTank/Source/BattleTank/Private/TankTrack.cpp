// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle){
    auto Time = GetWorld()->GetTimeSeconds();
    auto Name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("%f: %s Throttle: %f"), Time, *Name, Throttle);

    //se define la fuerza aplicada para moverse
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    //la ubicacion del objeto a aplicar la fuerza, que es la ubicaconde los tracks
    auto ForceLocation = GetComponentLocation();
    //se obtiene el root component, que es el que queremos mover, el tanque pues
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    //se aplica la fuerza calculada
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}