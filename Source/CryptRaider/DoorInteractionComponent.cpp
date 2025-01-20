// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorInteractionComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	startLeftDoorRotation = leftHingeDoor->GetRelativeRotation();
	startRightDoorRotation = rightHingeDoor->GetRelativeRotation();
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (currentState == DoorState::Opening) 
	{
		FRotator currentLeftHingeDoorRotation = leftHingeDoor->GetRelativeRotation();
		FRotator currentRightHingeDoorRotation = rightHingeDoor->GetRelativeRotation();

		leftHingeDoor->SetRelativeRotation(FMath::RInterpConstantTo(currentLeftHingeDoorRotation, leftHingeDoorOpenRotation, DeltaTime, openSpeed));
		rightHingeDoor->SetRelativeRotation(FMath::RInterpConstantTo(currentRightHingeDoorRotation, rightHingeDoorOpenRotation, DeltaTime, openSpeed));

		if ((leftHingeDoor->GetRelativeRotation() - leftHingeDoorOpenRotation).IsNearlyZero()) 
		{
			currentState = DoorState::Opened;
		}
	} 
	else if (currentState == DoorState::Closing)
	{
		FRotator currentLeftHingeDoorRotation = leftHingeDoor->GetRelativeRotation();
		FRotator currentRightHingeDoorRotation = rightHingeDoor->GetRelativeRotation();

		leftHingeDoor->SetRelativeRotation(FMath::RInterpConstantTo(currentLeftHingeDoorRotation, startLeftDoorRotation, DeltaTime, openSpeed));
		rightHingeDoor->SetRelativeRotation(FMath::RInterpConstantTo(currentRightHingeDoorRotation, startRightDoorRotation, DeltaTime, openSpeed));

		if ((leftHingeDoor->GetRelativeRotation() - startLeftDoorRotation).IsNearlyZero())
		{
			currentState = DoorState::Closed;
		}
	}
}

void UDoorInteractionComponent::Open()
{
	interactionTime = 0;
	currentState = DoorState::Opening;
}

void UDoorInteractionComponent::Close()
{
	interactionTime = 0;
	currentState = DoorState::Closing;
}

DoorState UDoorInteractionComponent::GetCurrentState() const
{
    return currentState;
}
