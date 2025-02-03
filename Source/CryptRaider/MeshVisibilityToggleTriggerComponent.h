// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerComponent.h"
#include "MeshVisibilityToggleTriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMeshVisibilityToggleTriggerComponent : public UTriggerComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	void ToggleTargetMeshesVisibility();
	virtual void OnTriggerEnter(AActor* OverlappingActor) override;
	virtual void OnTriggerExit() override;

private:
	UPROPERTY(EditAnywhere)
	TArray<AActor*> TargetActors;
};
