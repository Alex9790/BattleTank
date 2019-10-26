// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed){

    auto Time = GetWorld()->GetTimeSeconds();
    //mover el Barrel la cantidad justa por frame
    UE_LOG(LogTemp, Warning, TEXT("%f: UTankBarrel - RelativeSpeed = %f"), Time, RelativeSpeed);

	//dada una maxima velocidad de elevacion y tiempo por frame
}
