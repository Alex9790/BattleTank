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
	UTankTrack();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//define el Throttle
	UFUNCTION(BlueprintCallable, Category = Input)	//define a un metodo que se puede llamar desde un BluePrint
	void SetThrottle(float Throttle);

	//velocidad maxima
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; //se asume Tank pesa 40tons, 1g de aceleracion 

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
