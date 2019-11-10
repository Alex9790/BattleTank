// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward Declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:		
		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;

	protected:
		UFUNCTION(BlueprintCallable, category = Setup)
		ATank* GetControlledTank() const;

	private:
		
		void AimTowardsCrosshair();

		bool GetSightRayHitLocation(FVector& HitLocation) const;

		UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;

		UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333;

		UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0; //la distancia se mide en centimetros, 10km = 1000000cm

		bool GetLookDirection(FVector2D ScreenLocation, FVector& CameraWorldLocation, FVector& LookDirection) const;

		bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
