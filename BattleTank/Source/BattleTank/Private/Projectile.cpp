// Fill out your copyright notice in the Description page of Project Settings.


#include "Particles/ParticleSystemComponent.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//definir componente heredado
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	
	//para evitar que realice movimiento hasta que realmente hayamos disparado
	ProjectileMovement->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);	//activar "Simulation Generates Hit Events" por defecto
	CollisionMesh->SetVisibility(false);								//visualisar el projectile

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	//LaunchBlast->AttachTo(RootComponent);	//si no me equivoco esto es para que las particulas de peguen al projectil
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate=false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit); //AProjectile no es un Component, pero CollisionMesh si
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

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	//UE_LOG(LogTemp, Warning, TEXT("Hit"));
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
}
