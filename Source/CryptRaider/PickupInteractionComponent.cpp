// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupInteractionComponent.h"

// Sets default values for this component's properties
UPickupInteractionComponent::UPickupInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPickupInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	Primitive = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	
	TArray<UStaticMeshComponent*> MeshComponents;
	GetOwner()->GetComponents(MeshComponents);

	for (auto MeshComponent : MeshComponents)
	{
		CollisionMap[MeshComponent] = MeshComponent->GetCollisionResponseToChannel(ECC_Pawn);
	}
}

// Called every frame
void UPickupInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Handler != nullptr && Primitive != nullptr && CachedInteractor != nullptr)
	{
		FVector TargetLocation = CachedInteractor->GetComponentLocation() + CachedInteractor->GetForwardVector() * CachedInteractor->GetHoldDistance();
		Handler->SetTargetLocationAndRotation(TargetLocation, CachedInteractor->GetComponentRotation());
	}
}

bool UPickupInteractionComponent::TryInteract(UInteractor& Interactor)
{
	this->CachedInteractor = &Interactor;

	AActor* Owner = Interactor.GetOwner();
	Handler = Owner->FindComponentByClass<UPhysicsHandleComponent>();

	if (Handler != nullptr && Primitive != nullptr)
	{
		if (Handler->GetGrabbedComponent() == Primitive)
		{
			UE_LOG(LogTemp, Display, TEXT("Release %s!"), *Primitive -> GetName());
			Handler->ReleaseComponent();

			for (auto CollisionCache : CollisionMap)
			{
				UE_LOG(LogTemp, Display, TEXT("Setting %s collision to %d"), *CollisionCache.first->GetName(), CollisionCache.second);
				
				CollisionCache.first->SetCollisionResponseToChannel(ECC_Pawn, CollisionCache.second);
				CollisionCache.first->UpdateCollisionProfile();
			}
			
			return false;
		}
		
		for (auto CollisionCache : CollisionMap)
		{
			UE_LOG(LogTemp, Display, TEXT("Setting %s collision to %d (ignore)"), *CollisionCache.first->GetName(), ECR_Ignore);
			CollisionCache.first->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
			CollisionCache.first->UpdateCollisionProfile();
		}

		UE_LOG(LogTemp, Display, TEXT("Pick %s up!"), *Primitive -> GetName());
		FVector GrabPoint = Primitive->GetComponentLocation() + Primitive->GetComponentRotation().RotateVector(GrabAnchorLocation);
		Handler->GrabComponentAtLocationWithRotation(Primitive, NAME_None, GrabPoint, Interactor.GetComponentRotation());
		
		return true;
	}
	
	return false;
}

bool UPickupInteractionComponent::IsInteractable() const
{
	return true;
}

FString UPickupInteractionComponent::GetInteractionPrompt() const
{
	if (Handler != nullptr && Handler->GetGrabbedComponent() == Primitive)
	{
		return DropInteractionPrompt;
	}
	return PickUpInteractionPrompt;
}

