// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "InteractionTracer.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOPPINGHORROR_API UInteractionTracer : public UActorComponent
{
	GENERATED_BODY()

	friend class ASHPlayer;

public:	
	UInteractionTracer();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Interaction");
	bool DoTrace = true;

	UPROPERTY(BlueprintReadOnly, Category="Interaction")
	bool LookingAtInteractable = false;

	UPROPERTY(BlueprintReadOnly, Category="Interaction")
	AActor* HitActor;

	UFUNCTION(BlueprintCallable, Category="Interaction")
	AActor* Trace(float Distance, ETraceTypeQuery Channel, UCameraComponent* Camera);

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void Interact();
	
private:
};
