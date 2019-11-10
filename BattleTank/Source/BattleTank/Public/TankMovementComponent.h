// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Clase para gestionar el movimiento del Tanque para las AI
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSer);

	UFUNCTION(BlueprintCallable, Category = Input)	//define a un metodo que se puede llamar desde un BluePrint
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)	//define a un metodo que se puede llamar desde un BluePrint
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)	//define a un metodo que se puede llamar desde un BluePrint
	void IntendTurnLeft(float Throw);

	// metodo llamado por el AI Pathfinding en TankAIController
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
