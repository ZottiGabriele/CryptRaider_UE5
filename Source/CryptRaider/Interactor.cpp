// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactor.h"

#include "Interactable.h"
#include "ViewportInteractionTypes.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UInteractor::UInteractor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UInteractor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (bDebugEnabled)
	{
		FVector LineStart = GetComponentLocation();
		FVector LineEnd = LineStart + GetForwardVector() * MaxInteractDistance;
		
		FHitResult Hit;
		FCollisionShape Shape = FCollisionShape::MakeSphere(InteractRadius);
	
		bool bIsHitting = GetWorld()->SweepSingleByChannel(Hit, LineStart, LineEnd, FQuat::Identity, ECC_GameTraceChannel2, Shape);
		if (bIsHitting)
		{
			DrawDebugLine(GetWorld(), LineStart, Hit.ImpactPoint, FColor::Red);
			DrawDebugSphere(GetWorld(), Hit.Location, InteractRadius, 20, FColor::Blue);
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, InteractRadius, 20, FColor::Green);
		}
		else
		{
			DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Red);
			DrawDebugSphere(GetWorld(), LineEnd, InteractRadius, 20, FColor::Red);
		}
	}
}

bool UInteractor::TryInteract()
{
	FVector LineStart = GetComponentLocation();
	FVector LineEnd = LineStart + GetForwardVector() * MaxInteractDistance;

	FHitResult Hit;
	FCollisionShape Shape = FCollisionShape::MakeSphere(InteractRadius);
	
	bool bIsHitting = GetWorld()->SweepSingleByChannel(Hit, LineStart, LineEnd, FQuat::Identity, ECC_GameTraceChannel2, Shape);
	if (bIsHitting)
	{
		AActor* Actor = Hit.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Hit: %s"), *Actor->GetName());

		IInteractable* Interactable = Actor->FindComponentByInterface<IInteractable>();
		if (Interactable && Interactable->IsInteractable())
		{
			UE_LOG(
			LogTemp,
			Display,
			TEXT("%s has an IInteractable component. Interacting with prompt: %s"),
			*Actor->GetName(),
			*Interactable->GetInteractionPrompt());

			InteractionLocation = Hit.ImpactPoint;
			Interactable->TryInteract(*this);
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Hit"));
	}

	return bIsHitting;
}

float UInteractor::GetInteractRadius() const
{
	return InteractRadius;
}

float UInteractor::GetHoldDistance() const
{
	return HoldDistance;
}

FVector UInteractor::GetInteractLocation() const
{
	return InteractionLocation;
}
