// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack(){
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


// Called every frame
void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
}

void UTankTrack::ApplySidewaysForce()
{
	//calcular la velocidad de deslizamiento
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//obtener la aceleracion requerida para corregir deslizamiento en este frame
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector());
	//calcular y aplicar Sideways para (F = m*a)
	//para obtener la masa del Actor se de castear el Root(SceneComponent) a StaticMeshComponent    
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //se divide entre dos porque hay dos Tracks

	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle){
    //auto Time = GetWorld()->GetTimeSeconds();
    //auto Name = GetName();
    //UE_LOG(LogTemp, Warning, TEXT("%f: %s Throttle: %f"), Time, *Name, Throttle);

	//CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 2);
	CurrentThrottle = CurrentThrottle + Throttle;
}

void UTankTrack::DriveTrack()
{
	//se define la fuerza aplicada para moverse
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	//la ubicacion del objeto a aplicar la fuerza, que es la ubicaconde los tracks
	auto ForceLocation = GetComponentLocation();
	//se obtiene el root component, que es el que queremos mover, el tanque pues
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//se aplica la fuerza calculada
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	//UE_LOG(LogTemp, Warning, TEXT("Hit"));
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}