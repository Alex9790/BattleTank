// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSer){
    if(!LeftTrackToSet || !RightTrackToSer){return;}
    
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSer;
}

void UTankMovementComponent::IntendMoveForward(float Throw){
    //auto Time = GetWorld()->GetTimeSeconds();
    //auto Name = GetName();
    //UE_LOG(LogTemp, Warning, TEXT("%f: %s Throw: %f"), Time, *Name, Throw);

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);    
}