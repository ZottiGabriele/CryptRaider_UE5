// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionTriggerComponent.h"


void UDoorInteractionTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Door != nullptr)
	{
		DoorInteraction = Door->FindComponentByClass<UDoorInteractionComponent>();
	}
}

void UDoorInteractionTriggerComponent::OnTriggerEnter(AActor* OverlappingActor)
{
	Super::OnTriggerEnter(OverlappingActor);

	if (DoorInteraction != nullptr && OnTriggerEnterInteractions.Num() > 0)
	{
		for (auto Interaction : OnTriggerEnterInteractions)
		{
			DoorInteraction->ExecuteInteraction(Interaction);
		}
	}
}

void UDoorInteractionTriggerComponent::OnTriggerExit()
{
	Super::OnTriggerExit();

	if (DoorInteraction != nullptr && OnTriggerExitInteractions.Num() > 0)
	{
		for (auto Interaction : OnTriggerExitInteractions)
		{
			DoorInteraction->ExecuteInteraction(Interaction);
		}
	}
}