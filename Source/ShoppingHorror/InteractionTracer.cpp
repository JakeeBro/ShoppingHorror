// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionTracer.h"

#include "Interactable.h"

UInteractionTracer::UInteractionTracer()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UInteractionTracer::BeginPlay()
{
	Super::BeginPlay();

	
}

void UInteractionTracer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

AActor* UInteractionTracer::Trace(float Distance, ETraceTypeQuery Channel, UCameraComponent* Camera)
{
	if (!DoTrace)
	{
		LookingAtInteractable = false;
		HitActor = nullptr;
		return HitActor;
	}

	FVector Start = Camera->GetComponentLocation();
	FVector End = Camera->GetComponentLocation() + (Camera->GetForwardVector() * Distance);

	FHitResult HitResult;

	FCollisionQueryParams CollisionParams;
	CollisionParams.bTraceComplex = true;
	CollisionParams.AddIgnoredActor(this->GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, UEngineTypes::ConvertToCollisionChannel(Channel), CollisionParams))
	{
		HitActor = HitResult.GetActor();

		if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			LookingAtInteractable = true;

			return HitActor;
		}
		LookingAtInteractable = false;
		HitActor = nullptr;
		return HitActor;
	}
	LookingAtInteractable = false;
	HitActor = nullptr;
	return HitActor;
}

void UInteractionTracer::Interact()
{
	if (!LookingAtInteractable || HitActor == nullptr) return;

	IInteractable::Execute_Interact(HitActor, this->GetOwner());
}
