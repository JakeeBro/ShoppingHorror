// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Timer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerEnd);

UCLASS()
class SHOPPINGHORROR_API ATimer : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimer();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category="Timer")
	FOnTimerEnd OnTimerEnd;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Timer")
	float LengthInSeconds;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Timer")
	float SecondsRemaining;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Timer")
	float ActiveSecond;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Timer")
	bool TimerTick;

	UFUNCTION()
	void ReduceTime();

	UFUNCTION(BlueprintCallable, Category="Timer")
	FString SecondsToMinutes(float Seconds);
};
