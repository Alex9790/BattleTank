// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSer){
    if(!LeftTrackToSet || !RightTrackToSer){return;}
    
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSer;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we're replacing the functionality
	//auto TankName = GetOwner()->GetName();
    //UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString)
    //vector direccion hacia el objetivo
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    //vector que contiene la direccion en la que el tanque apunta hacia adelante
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);   
    IntendMoveForward(ForwardThrow*3);

    auto GirarThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
    //UE_LOG(LogTemp, Warning, TEXT("GirarThrow %f"), GirarThrow);
    IntendTurnRight(GirarThrow*5);
    /*if(GirarThrow > 0){
        IntendTurnRight(GirarThrow*4);
    }else{
        IntendTurnLeft(GirarThrow*4);
    }*/
}

void UTankMovementComponent::IntendMoveForward(float Throw){
    //auto Time = GetWorld()->GetTimeSeconds();
    //auto Name = GetName();
    //UE_LOG(LogTemp, Warning, TEXT("%f: %s Throw: %f"), Time, *Name, Throw);

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);    
}

void UTankMovementComponent::IntendTurnRight(float Throw){
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);    
}

void UTankMovementComponent::IntendTurnLeft(float Throw){
    LeftTrack->SetThrottle(-Throw);
    RightTrack->SetThrottle(Throw);    
}