// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupInteractionComponent.h"

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
}


// Called every frame
void UPickupInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UPickupInteractionComponent::TryInteract()
{
	UE_LOG(LogTemp, Display, TEXT("Pick me up!"));
	return true;
}

bool UPickupInteractionComponent::IsInteractable()
{
	return true;
}

FString UPickupInteractionComponent::GetInteractionPrompt()
{
	return "Pick up";
}

