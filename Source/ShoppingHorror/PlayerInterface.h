// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory.h"
#include "ListTracker.h"
#include "SHPlayer.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SHOPPINGHORROR_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Player")
	ASHPlayer* GetPlayer();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Player")
	UInventory* GetInventory();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Player")
	UListTracker* GetListTracker();
};
