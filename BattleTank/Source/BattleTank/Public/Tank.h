// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; //Forward Declaration
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sets default values for this pawn's properties
	ATank();

	//Metodo que se encarga de disparar proyectles
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

private:
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000; //velocidad de 1000 m/s = 100000 cm/s - Valor por defecto, el diseñador los escogera cuando llegue el momento	

	UPROPERTY(EditAnywhere, Category = Firing)
	TSubclassOf<AProjectile> ProjectileBlueprint;	//Alternativa: UClass* ProjectileBlueprint

	//tiempo delay entre disparos
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr;

};
