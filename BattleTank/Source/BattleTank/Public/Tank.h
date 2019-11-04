// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; //Forward Declaration
class UTankAimingComponent;
class UTankMovementComponent;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

	//UPROPERTY(BlueprintReadOnly)
	//UTankMovementComponent* TankMovementComponent = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);

	// Sets default values for this pawn's properties
	ATank();

	//Metodo que se encarga de disparar proyectles
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

private:
	UFUNCTION(BlueprintCallable, Category = Setup)	//define a un metodo que se puede llamar desde un BluePrint
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)	//define a un metodo que se puede llamar desde un BluePrint
	void SetTurretReference(UTankTurret* TurretToSet);

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000; //velocidad de 1000 m/s = 100000 cm/s - Valor por defecto, el diseñador los escogera cuando llegu ele momento	

	UPROPERTY(EditAnywhere, Category = Firing)
	TSubclassOf<AProjectile> ProjectileBlueprint;	//Alternativa: UClass* ProjectileBlueprint

	//Referencia local del barrel para generar proyectiles
	UTankBarrel* Barrel = nullptr;

	//tiempo delay entre disparos
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

};
