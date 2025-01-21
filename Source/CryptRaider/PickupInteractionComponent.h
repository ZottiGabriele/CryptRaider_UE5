// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PickupInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UPickupInteractionComponent : public UActorComponent, public IInteractable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool TryInteract(UInteractor& Interactor) override;
	virtual bool IsInteractable() override;
	virtual FString GetInteractionPrompt() override;

private:
	UPrimitiveComponent* Primitive;
	UInteractor* CachedInteractor;
	UPhysicsHandleComponent* Handler;
};
