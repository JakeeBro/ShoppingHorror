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

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void AddItem(AItem* Item, FItemProperties ItemProperties);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RemoveItem(AItem* Item, bool Clear);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory")
	TMap<AItem*, FItemProperties> ItemPropertiesMap;

	// REWRITE
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory")
	// TMap<AItem*, int32> ItemsMap;
	
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory")
	// TMap<AItem*, FItemProperties> PropertiesMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<AItem*> Items;

	// TODO Fix Items Array Deleting itself at runtime
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<TSubclassOf<AItem>> ItemClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<FItemProperties> Properties;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<int32> Values;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory")
	FItemProperties ActiveItem;

	UPROPERTY()
	FItemProperties NullItemProperties;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory")
	int32 ActiveIndex;

	UPROPERTY(EditAnywhere, Category="Inventory")
	bool Print = false;

	// FUNCTIONS
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void AddToInventory(AItem* Item, FItemProperties ItemProperties);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	FItemProperties RemoveFromInventory(FItemProperties ItemProperties);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void UpdateActiveIndex(float AxisValue);

protected:
	virtual void BeginPlay() override;

public:	
	
};
