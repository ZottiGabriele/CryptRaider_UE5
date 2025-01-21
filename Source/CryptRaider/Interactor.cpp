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

	// ...
}


// Called when the game starts
void UInteractor::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInteractor::TryInteract()
{
	FVector LineStart = GetComponentLocation();
	FVector LineEnd = LineStart + GetForwardVector() * MaxGrabDistance;
	
	DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Red);

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

			Interactable->TryInteract();
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Hit"));
	}

	return bIsHitting;
}
