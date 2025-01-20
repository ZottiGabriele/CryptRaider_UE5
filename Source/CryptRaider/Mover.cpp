// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
	startPosition = owner->GetActorLocation();
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ShouldMove) return;

	FVector currentPosition = owner->GetActorLocation();
	FVector targetPosition = startPosition + MoveOffset;
	float speed = FVector::Distance(startPosition, targetPosition) / MoveTime;
	FVector newPosition = FMath::VInterpConstantTo(currentPosition, targetPosition, DeltaTime, speed);

	UE_LOG(LogTemp, Display, TEXT("New Position %s"), *newPosition.ToCompactString());

	owner->SetActorLocation(newPosition);

	if (newPosition == targetPosition) 
	{
		ShouldMove = false;
		startPosition = targetPosition;
	}
}

