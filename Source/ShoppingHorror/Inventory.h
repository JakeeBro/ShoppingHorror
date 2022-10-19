// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOPPINGHORROR_API UInventory : public UActorComponent
{
	GENERATED_BODY()

	friend class ASHPlayer;

public:	
	UInventory();
	
	// Array containing the Class of each Item held
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<TSubclassOf<AItem>> ItemClasses;

	// Array containing the Name and Mesh of each Item held
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<FItemProperties> Properties;

	// Array containing the amount of each Item held
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<int32> Values;

	// Reference to the Name and Mesh of the Item at the Active Index
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory")
	FItemProperties ActiveItem;

	// Empty Item Name and Mesh for resetting the Held Item
	UPROPERTY()
	FItemProperties NullItemProperties;

	// Value determining which Index to access arrays with
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory")
	int32 ActiveIndex;

	UPROPERTY(EditAnywhere, Category="Inventory")
	bool Print = false;

	// FUNCTIONS
	// Adds an Item to the Inventory if the Passed Item's Class is not already within it, Otherwise Increases the Value of the Passed Item's Index
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void AddToInventory(AItem* Item, FItemProperties ItemProperties);

	// Removes an Item from the Inventory, Outputs a Bool to determine if an Item should Spawn as a result of the removal
	UFUNCTION(BlueprintCallable, Category="Inventory")
	FItemProperties RemoveFromInventory(FItemProperties ItemProperties, bool& Continue);

	// Returns the Values of the Active Index from each Array
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void ReadActiveIndex(TSubclassOf<AItem>& IndexClass, FItemProperties& IndexProperties, int32& IndexValue);

	// Updates the ActiveIndex based on a Given Axis Value
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void UpdateActiveIndex(float AxisValue);

protected:
	virtual void BeginPlay() override;

public:	
	
};
