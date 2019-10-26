// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TankBarrel.generated.h"

/**
 * Contiene las Propiedades del Barrel y metodo Elevate
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent)/*, hidecategories = ("Collision") */)
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//RelativeSpeed - -1 la minima altura que puede alcanzar, 1 la maxima altura que puede alcanzar
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20; //Sensible Default

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0; 
};
