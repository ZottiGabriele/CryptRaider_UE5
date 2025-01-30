// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoorInteractionComponent.h"
#include "TriggerComponent.h"
#include "DoorInteractionTriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UDoorInteractionTriggerComponent : public UTriggerComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	AActor* Door;

	UPROPERTY(EditAnywhere)
	TArray<DoorInteraction> OnTriggerEnterInteractions;

	UPROPERTY(EditAnywhere)
	TArray<DoorInteraction> OnTriggerExitInteractions;
	
	UDoorInteractionComponent* DoorInteraction;

protected:
	virtual void BeginPlay() override;
	
	virtual void OnTriggerEnter(AActor* OverlappingActor) override;
	virtual void OnTriggerExit() override;
};
