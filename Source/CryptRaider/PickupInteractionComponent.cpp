// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupInteractionComponent.h"

#include "Materials/MaterialExpressionLocalPosition.h"

// Sets default values for this component's properties
UPickupInteractionComponent::UPickupInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPickupInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	Primitive = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
}


// Called every frame
void UPickupInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Handler != nullptr && Primitive != nullptr && CachedInteractor != nullptr)
	{
		FVector TargetLocation = CachedInteractor->GetComponentLocation() + CachedInteractor->GetForwardVector() * CachedInteractor->HoldDistance;
		Handler->SetTargetLocationAndRotation(TargetLocation, CachedInteractor->GetComponentRotation());
	}
}

bool UPickupInteractionComponent::TryInteract(UInteractor& Interactor)
{
	this->CachedInteractor = &Interactor;

	AActor* Owner = Interactor.GetOwner();
	Handler = Owner->FindComponentByClass<UPhysicsHandleComponent>();

	if (Handler != nullptr && Primitive != nullptr)
	{
		if (Handler->GetGrabbedComponent() == Primitive)
		{
			UE_LOG(LogTemp, Display, TEXT("Release %s!"), *Primitive -> GetName());
			Handler->ReleaseComponent();
			return false;
		}
		
		UE_LOG(LogTemp, Display, TEXT("Pick %s up!"), *Primitive -> GetName());
		
		Handler->GrabComponentAtLocationWithRotation(Primitive, NAME_None, Interactor.InteractionLocation, Interactor.GetComponentRotation());
		return true;
	}
	
	return false;
}

bool UPickupInteractionComponent::IsInteractable()
{
	return true;
}

FString UPickupInteractionComponent::GetInteractionPrompt()
{
	return "Pick up";
}

