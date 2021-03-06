// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//inherited Components
	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	if (!GetAttachParentActor()) { return; }

	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }

	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Cast<UPrimitiveComponent>(Axle), NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Cast<UPrimitiveComponent>(Axle), NAME_None, Cast<UPrimitiveComponent>(Wheel), NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

