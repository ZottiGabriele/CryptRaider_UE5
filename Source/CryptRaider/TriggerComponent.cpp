// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* OverlappingActor = GetValidOverlappingActor();
	
	if (!HasEntered && OverlappingActor != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("ENTER!"));
		HasEntered = true;
		OnTriggerEnter(OverlappingActor);
	}
	else if (HasEntered && OverlappingActor == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("EXIT!"));
		HasEntered = false;
		OnTriggerExit();
	}
}

AActor* UTriggerComponent::GetValidOverlappingActor() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->ActorHasTag(FilterTag))
		{
			return Actor;
		}
	}
	return nullptr;
}

