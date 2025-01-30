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

	CurrentState = StartingState;

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
	if (IsLocked) return;
	
	UE_LOG(LogTemp, Display, TEXT("Opening Door %s"), *GetOwner()->GetName());
	InteractionTime = 0;
	CurrentState = DoorState::Opening;
}

void UDoorInteractionComponent::Close()
{
	if (IsLocked) return;
	
	UE_LOG(LogTemp, Display, TEXT("Closing Door %s"), *GetOwner()->GetName());
	InteractionTime = 0;
	CurrentState = DoorState::Closing;
}

void UDoorInteractionComponent::Unlock()
{
	UE_LOG(LogTemp, Display, TEXT("Unlocking Door %s"), *GetOwner()->GetName());
	IsLocked = false;
}

void UDoorInteractionComponent::Lock()
{
	UE_LOG(LogTemp, Display, TEXT("Locking Door %s"), *GetOwner()->GetName());
	IsLocked = true;
}

void UDoorInteractionComponent::ExecuteInteraction(DoorInteraction Interaction)
{
	switch (Interaction)
	{
		case DoorInteraction::Close:
			Close();
			break;
		case DoorInteraction::Open:
			Open();
			break;
		case DoorInteraction::Lock:
			Lock();
			break;
		case DoorInteraction::Unlock:
			Unlock();
			break;
		case DoorInteraction::SetInteractableTrue:
			SetInteractable(true);
			break;
		case DoorInteraction::SetInteractableFalse:
			SetInteractable(false);
			break;
	}
}

DoorState UDoorInteractionComponent::GetCurrentState() const
{
    return CurrentState;
}

bool UDoorInteractionComponent::TryInteract(UInteractor& Interactor)
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

bool UDoorInteractionComponent::IsInteractable() const
{
	return bInteractionEnabled && (CurrentState == DoorState::Opened || CurrentState == DoorState::Closed);
}

void UDoorInteractionComponent::SetInteractable(const bool InteractionEnabled)
{
	bInteractionEnabled = InteractionEnabled;
}

FString UDoorInteractionComponent::GetInteractionPrompt() const
{
	if (IsLocked)
	{
		return LockedInteractionPrompt;
	}
	
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
