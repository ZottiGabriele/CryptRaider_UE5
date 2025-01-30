// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnTriggerEnter(AActor* OverlappingActor) {}
	virtual void OnTriggerExit() {}

public:
	UTriggerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	FName FilterTag;

	bool HasEntered;
	
	AActor* GetValidOverlappingActor() const;
};
