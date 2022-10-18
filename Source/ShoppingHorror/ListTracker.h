// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/ActorComponent.h"
#include "ListTracker.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOPPINGHORROR_API UListTracker : public UActorComponent
{
	GENERATED_BODY()

	friend class ASHPlayer;

public:	
	UListTracker();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// REQUIRED Inventory
	UFUNCTION(BlueprintCallable, Category="List Tracker")
	AItem* AddToHeldList(AItem* Item);

	// TODO Spawn Items
	UFUNCTION(BlueprintCallable, Category="List Tracker")
	bool RemoveFromHeldList(AItem* Item);
	
	// REQUIRED Inventory / Placement / Input
	UFUNCTION(BlueprintCallable, Category="List Tracker")
	void UpdateActiveHeldIndex(float AxisValue);

	// REQUIRED UI
	UFUNCTION(BlueprintCallable, Category="List Tracker")
	FString UpdateActiveHeldItemName();

	// REQUIRED UI
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="List Tracker")
	FString ActiveHeldItemName;

protected:
	virtual void BeginPlay() override;

	// TODO Quest Tracking
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="List Tracker")
	TMap<TSubclassOf<AItem>, int32> TargetList;

	// REQUIRED Inventory
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="List Tracker")
	TMap<AItem*, int32> HeldList;

	// REQUIRED Inventory / Placement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="List Tracker")
	int32 ActiveHeldIndex;

	// REQUIRED Inventory / Placement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="List Tracker")
	AItem* ActiveHeldItem;

	// REQUIRED Debug
	UPROPERTY(EditAnywhere, Category="List Tracker")
	bool Print = false;
};
