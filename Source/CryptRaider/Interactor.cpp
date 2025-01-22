// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactor.h"
#include "Interactable.h"
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


bool UInteractor::SweepForInteractables()
{
	FVector LineStart = GetComponentLocation();
	FVector LineEnd = LineStart + GetForwardVector() * MaxInteractDistance;
	
	FCollisionShape Shape = FCollisionShape::MakeSphere(InteractRadius);

	bool bIsHitting = GetWorld()->SweepSingleByChannel(CurrentHit, LineStart, LineEnd, FQuat::Identity, ECC_GameTraceChannel2, Shape);
	if (bIsHitting)
	{
		AActor* Actor = CurrentHit.GetActor();
		UActorComponent* InteractableComponent = Actor->FindComponentByInterface(UInteractable::StaticClass());
		if (InteractableComponent)
		{
			IInteractable* Interactable = Cast<IInteractable>(InteractableComponent);
			LastHitInteractable.SetInterface(Interactable);
			LastHitInteractable.SetObject(InteractableComponent);
		}
		
		if (bDebugEnabled)
		{
			DrawDebugLine(GetWorld(), LineStart, CurrentHit.ImpactPoint, FColor::Red);
			DrawDebugSphere(GetWorld(), CurrentHit.Location, InteractRadius, 20, FColor::Blue);
			DrawDebugSphere(GetWorld(), CurrentHit.ImpactPoint, InteractRadius, 20, FColor::Green);
		}
	}
	else
	{
		if (bDebugEnabled)
		{
			DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Red);
			DrawDebugSphere(GetWorld(), LineEnd, InteractRadius, 20, FColor::Red);
		}
	}
	
	return bIsHitting;
}

// Called every frame
void UInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInteractor::TryInteract()
{
	if (CurrentHit.bBlockingHit)
	{
		AActor* Actor = CurrentHit.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Hit: %s"), *Actor->GetName());

		IInteractable* Interactable = LastHitInteractable.GetInterface();
		if (Interactable && Interactable->IsInteractable())
		{
			UE_LOG(
			LogTemp,
			Display,
			TEXT("%s has an IInteractable component. Interacting with prompt: %s"),
			*Actor->GetName(),
			*Interactable->GetInteractionPrompt());
			
			Interactable->TryInteract(*this);
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Hit"));
	}

	return CurrentHit.bBlockingHit;
}

float UInteractor::GetInteractRadius() const
{
	return InteractRadius;
}

float UInteractor::GetHoldDistance() const
{
	return HoldDistance;
}

FHitResult UInteractor::GetCurrentHit() const
{
	return CurrentHit;
}

TScriptInterface<IInteractable> UInteractor::GetLastHitInteractable() const
{
	return LastHitInteractable;
}
