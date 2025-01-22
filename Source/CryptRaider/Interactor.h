// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Interactor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UInteractor : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool TryInteract();

	UFUNCTION(BlueprintCallable)
	bool SweepForInteractables();

	UFUNCTION(BlueprintCallable)
	FHitResult GetCurrentHit() const;

	UFUNCTION(BlueprintCallable)
	TScriptInterface<IInteractable> GetLastHitInteractable() const;
	
	float GetInteractRadius() const;
	float GetHoldDistance() const;

private:
	UPROPERTY(EditAnywhere)
	float MaxInteractDistance = 150;

	UPROPERTY(EditAnywhere)
	float InteractRadius = 25;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 120;

	UPROPERTY(EditAnywhere)
	bool bDebugEnabled = false;
	
	FHitResult CurrentHit;
	TScriptInterface<IInteractable> LastHitInteractable;
};
