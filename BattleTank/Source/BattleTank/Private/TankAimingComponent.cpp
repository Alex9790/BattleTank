// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	//para agregar un primer Reload
	LastFireTime = FPlatformTime::Seconds();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//se agrega logica para cambiar de color el Crosshair segun su estado
	if((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds){
		FiringState = EFiringState::Reloading;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet){
    if(!ensure(BarrelToSet || TurretToSet)){return;}
    
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation){

	if(!ensure(Barrel)){return;}

	auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("TankAimingComponent - %s Apuntando en: %s. Desde el Barrel %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation);
	//UE_LOG(LogTemp, Warning, TEXT("TankAimingComponent - %s LaunchSpeed = %f"), *OurTankName, LaunchSpeed);

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calcular OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
							(
								this,													//const UObject * WorldContextObject
								OutLaunchVelocity,										//FVector & TossVelocity
								StartLocation,											//FVector StartLocation
								HitLocation,											//FVector EndLocation
								LaunchSpeed,											//float TossSpeed
								false,														//bool bHighArc, default = false
								0,														//float CollisionRadius, default = 0 //creo que s lo que altera el resultado final de las balas
								0,														//float OverrideGravityZ, default 0 0
								ESuggestProjVelocityTraceOption::DoNotTrace				//ESuggestProjVelocityTraceOption::Type TraceOption,
																						//const FCollisionResponseParams & ResponseParam,
																						//const TArray< AActor * > & ActorsToIgnore,
																						//bool bDrawDebug
							);
	if(bHaveAimSolution){
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("TankAimingComponent - Apuntando en: %s"), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}else{
		//auto Time = GetWorld()->GetTimeSeconds();
    	//UE_LOG(LogTemp, Warning, TEXT("%f: No se encontró Solución."), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection){

	if(!ensure(Barrel || Turret)){return;}

	//encontrar la diferencia entre la Rotacion actual del Barrel y AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("TankAimingComponent - Apuntando en: %s"), *AimDirection.ToString());

	//dada una maxima velocidad de elevacion y tiempo por frame
	//mover el Barrel la cantidad justa por frame
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
	
}

void UTankAimingComponent::Fire(){

	if(!ensure(Barrel) && !ensure(ProjectileBlueprint)){return;}

	if(FiringState != EFiringState::Reloading){
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}