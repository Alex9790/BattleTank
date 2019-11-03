// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack se usa para definir la maxima velocidad del tanque
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//define el Throttle
	UFUNCTION(BlueprintCallable, Category = Input)	//define a un metodo que se puede llamar desde un BluePrint
	void SetThrottle(float Throttle);
};
