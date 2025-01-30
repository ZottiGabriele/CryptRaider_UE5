// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
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

UENUM(BlueprintType)
enum class DoorInteraction : uint8
{
	Close,
	Open,
	Lock,
	Unlock,
	SetInteractableTrue,
	SetInteractableFalse
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UDoorInteractionComponent : public UActorComponent, public IInteractable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	UStaticMeshComponent* RightHingeDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	UStaticMeshComponent* LeftHingeDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	FRotator LeftHingeDoorOpenRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	FRotator RightHingeDoorOpenRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float OpenSpeed;

	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Open();

	UFUNCTION(BlueprintCallable)
	void Close();

	UFUNCTION(BlueprintCallable)
	void Unlock();

	UFUNCTION(BlueprintCallable)
	void Lock();

	UFUNCTION(BlueprintCallable)
	void ExecuteInteraction(DoorInteraction Interaction);
	
	UFUNCTION(BlueprintCallable)
	DoorState GetCurrentState() const;

	virtual bool TryInteract(UInteractor& Interactor) override;
	virtual bool IsInteractable() const override;
	virtual void SetInteractable(bool InteractionEnabled) override;
	virtual FString GetInteractionPrompt() const override;

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	FString OpenInteractionPrompt = "Open";

	UPROPERTY(EditAnywhere, Category = "Setup")
	FString CloseInteractionPrompt = "Close";

	UPROPERTY(EditAnywhere, Category = "Setup")
	FString LockedInteractionPrompt = "Locked";

	UPROPERTY(EditAnywhere, Category = "Setup")
	bool bInteractionEnabled = true;
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	DoorState StartingState;

	UPROPERTY(EditAnywhere, Category = "Setup")
	bool IsLocked;
	
	FRotator StartLeftDoorRotation;
	FRotator StartRightDoorRotation;
	DoorState CurrentState = DoorState::Closed;
	float InteractionTime = 0;

	bool TryGetDoorRotation(UStaticMeshComponent* Door, FRotator& CurrentDoorRotation);
};
