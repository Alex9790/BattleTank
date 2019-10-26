// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed){

    auto Time = GetWorld()->GetTimeSeconds();
    //mover el Barrel la cantidad justa por frame
    //UE_LOG(LogTemp, Warning, TEXT("%f: UTankBarrel - RelativeSpeed = %f"), Time, RelativeSpeed);

    //Clamp RelativeSpeed entre -1 y 1
    auto ClampRelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	//dada una maxima velocidad de elevacion y tiempo por frame
    //como cambia la elevacion en un frame en particular
    //RelativeSpeed * MaxDegreesPerSecond => Valor en grados por segundo
    auto ElevationChange = ClampRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    //Nueva elevacion = actual elevacion + cambio en elevacion
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    //Clamp elevacion entre Min y Max
    auto NewElevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

    //para finalmente rotar el Barrel
    SetRelativeRotation(FRotator(NewElevation, 0, 0));
}
