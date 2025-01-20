// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "Components/ActorComponent.h"
#include "DoorInteractionComponent.generated.h"


UENUM(BlueprintType)
enum class DoorState : uint8
{
	Closed,
	Opening,
	Opened,
	Closing
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* rightHingeDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* leftHingeDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator leftHingeDoorOpenRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator rightHingeDoorOpenRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float openSpeed;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Open();

	UFUNCTION(BlueprintCallable)
	void Close();

	UFUNCTION(BlueprintCallable)
	DoorState GetCurrentState() const;

private:
	FRotator startLeftDoorRotation;
	FRotator startRightDoorRotation;
	DoorState currentState = DoorState::Closed;
	float interactionTime = 0;
};
