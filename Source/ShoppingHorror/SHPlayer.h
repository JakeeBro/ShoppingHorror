// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionTracer.h"
#include "Inventory.h"
#include "ListTracker.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "SHPlayer.generated.h"

UCLASS()
class SHOPPINGHORROR_API ASHPlayer : public ACharacter
{
	GENERATED_BODY()
	
public:
	ASHPlayer();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// Axis Bindings
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	// Action Bindings
	void Place();
	
public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interaction")
	UInteractionTracer* InteractionTracer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Inventory")
	UInventory* Inventory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="List Tracker")
	UListTracker* ListTracker;
};
