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

	TryGetDoorRotation(LeftHingeDoor, StartLeftDoorRotation);
	TryGetDoorRotation(RightHingeDoor, StartRightDoorRotation);
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentState == DoorState::Opening) 
	{
		FRotator CurrentDoorRotation;
		if (TryGetDoorRotation(LeftHingeDoor, CurrentDoorRotation))
		{
			LeftHingeDoor->SetRelativeRotation(FMath::RInterpConstantTo(CurrentDoorRotation, LeftHingeDoorOpenRotation, DeltaTime, OpenSpeed));
			if ((LeftHingeDoor->GetRelativeRotation() - LeftHingeDoorOpenRotation).IsNearlyZero()) 
			{
				UE_LOG(LogTemp, Display, TEXT("Door is opened!"));
				CurrentState = DoorState::Opened;
			}
		}
		
		if (TryGetDoorRotation(RightHingeDoor, CurrentDoorRotation))
		{
			RightHingeDoor->SetRelativeRotation(FMath::RInterpConstantTo(CurrentDoorRotation, RightHingeDoorOpenRotation, DeltaTime, OpenSpeed));
			if ((RightHingeDoor->GetRelativeRotation() - RightHingeDoorOpenRotation).IsNearlyZero()) 
			{
				UE_LOG(LogTemp, Display, TEXT("Door is opened!"));
				CurrentState = DoorState::Opened;
			}
		}
	} 
	else if (CurrentState == DoorState::Closing)
	{
		FRotator CurrentDoorRotation;
		if (TryGetDoorRotation(LeftHingeDoor, CurrentDoorRotation))
		{
			LeftHingeDoor->SetRelativeRotation(FMath::RInterpConstantTo(CurrentDoorRotation, StartLeftDoorRotation, DeltaTime, OpenSpeed));
			if ((LeftHingeDoor->GetRelativeRotation() - StartLeftDoorRotation).IsNearlyZero()) 
			{
				UE_LOG(LogTemp, Display, TEXT("Door is closed!"));
				CurrentState = DoorState::Closed;
			}
		}
		
		if (TryGetDoorRotation(RightHingeDoor, CurrentDoorRotation))
		{
			RightHingeDoor->SetRelativeRotation(FMath::RInterpConstantTo(CurrentDoorRotation, StartRightDoorRotation, DeltaTime, OpenSpeed));
			if ((RightHingeDoor->GetRelativeRotation() - StartRightDoorRotation).IsNearlyZero()) 
			{
				UE_LOG(LogTemp, Display, TEXT("Door is closed!"));
				CurrentState = DoorState::Closed;
			}
		}
	}
}

void UDoorInteractionComponent::Open()
{
	UE_LOG(LogTemp, Display, TEXT("Opening Door!"));
	InteractionTime = 0;
	CurrentState = DoorState::Opening;
}

void UDoorInteractionComponent::Close()
{
	UE_LOG(LogTemp, Display, TEXT("Closing Door!"));
	InteractionTime = 0;
	CurrentState = DoorState::Closing;
}

DoorState UDoorInteractionComponent::GetCurrentState() const
{
    return CurrentState;
}

bool UDoorInteractionComponent::TryInteract()
{
	switch (CurrentState)
	{
	case DoorState::Closed:
		Open();
		break;
	case DoorState::Opened:
		Close();
		break;
	case DoorState::Opening:
	case DoorState::Closing:
		return false;
	}

	return true;
}

bool UDoorInteractionComponent::IsInteractable()
{
	return CurrentState == DoorState::Opened || CurrentState == DoorState::Closed;
}

FString UDoorInteractionComponent::GetInteractionPrompt()
{
	if (CurrentState == DoorState::Opened)
	{
		return CloseInteractionPrompt;	
	}

	if (CurrentState == DoorState::Closed)
	{
		return OpenInteractionPrompt;
	}
	
	return "";
}

bool UDoorInteractionComponent::TryGetDoorRotation(UStaticMeshComponent* Door, FRotator& CurrentDoorRotation)
{
	if (Door == nullptr) return false;
	
	CurrentDoorRotation = Door->GetRelativeRotation();
	return true;
}
