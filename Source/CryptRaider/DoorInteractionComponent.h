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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	FString OpenInteractionPrompt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	FString CloseInteractionPrompt;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Open();

	UFUNCTION(BlueprintCallable)
	void Close();

	UFUNCTION(BlueprintCallable)
	DoorState GetCurrentState() const;

	virtual bool TryInteract() override;
	virtual bool IsInteractable() override;
	virtual FString GetInteractionPrompt() override;

private:
	FRotator StartLeftDoorRotation;
	FRotator StartRightDoorRotation;
	DoorState CurrentState = DoorState::Closed;
	float InteractionTime = 0;

	bool TryGetDoorRotation(UStaticMeshComponent* Door, FRotator& CurrentDoorRotation);
};
