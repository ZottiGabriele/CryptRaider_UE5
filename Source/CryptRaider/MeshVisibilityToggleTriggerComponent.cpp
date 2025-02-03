// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshVisibilityToggleTriggerComponent.h"


void UMeshVisibilityToggleTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMeshVisibilityToggleTriggerComponent::OnTriggerEnter(AActor* OverlappingActor)
{
	Super::OnTriggerEnter(OverlappingActor);
	ToggleTargetMeshesVisibility();
}

void UMeshVisibilityToggleTriggerComponent::OnTriggerExit()
{
	Super::OnTriggerExit();
	ToggleTargetMeshesVisibility();
}

void UMeshVisibilityToggleTriggerComponent::ToggleTargetMeshesVisibility()
{
	TInlineComponentArray<UStaticMeshComponent*> MeshComponents;
	
	for (AActor* Actor : TargetActors)
	{
		Actor->GetComponents<UStaticMeshComponent>(MeshComponents);

		for (UStaticMeshComponent* MeshComponent : MeshComponents)
		{
			MeshComponent->ToggleVisibility();
		}
	}
}
