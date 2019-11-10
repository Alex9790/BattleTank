// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Forward Declaration
class ATank; 

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	public:
		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;		 

private: 
	ATank* ControlledTank = nullptr;
	ATank* PlayerTank = nullptr;

	//que tan cerca se puede acercar el AI al jugador (en centimetros)
	float AcceptanceRadius = 3000;
};
