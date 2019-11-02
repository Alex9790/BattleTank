// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//definir componente heredado
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	
	//para evitar que realice movimiento hasta que realmente hayamos disparado
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed){
	auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: Dispara Proyectil. A una Velocidad: %f"), Time, Speed);

	//dar movimiento al proyectil, en direccion hacia adelante a una velocidad definida
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	//se activa el movimiento del actor
	ProjectileMovement->Activate();
}
