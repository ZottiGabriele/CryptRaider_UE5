// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	bHasEntered = bIgnoreFirstEnter;
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* OverlappingActor = GetValidOverlappingActor();
	
	if (!bHasEntered && OverlappingActor != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("ENTER!"));
		bHasEntered = true;
		OnTriggerEnter(OverlappingActor);
	}
	else if (bHasEntered && OverlappingActor == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("EXIT!"));
		bHasEntered = false;
		OnTriggerExit();
	}
}

AActor* UTriggerComponent::GetValidOverlappingActor() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	
	for (AActor* Actor : OverlappingActors)
	{
		for (FName Tag : FilterTags)
		{
			if (Actor->ActorHasTag(Tag))
			{
				return Actor;
			}
		}
	}
	return nullptr;
}

