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

protected:
	virtual void BeginPlay() override;

	// TODO Quest Tracking
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="List Tracker")
	TMap<TSubclassOf<AItem>, int32> TargetList;

	// TODO Quest Tracking
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="List Tracker")
	TMap<AItem*, int32> HeldList;

	// Debug
	UPROPERTY(EditAnywhere, Category="List Tracker")
	bool Print = false;
};
