// Fill out your copyright notice in the Description page of Project Settings.

#include "Timer.h"

ATimer::ATimer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATimer::BeginPlay()
{
	Super::BeginPlay();

	SecondsRemaining = LengthInSeconds;
	TimerTick = true;
}

void ATimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TimerTick) return;

	ActiveSecond += DeltaTime;

	if (ActiveSecond < 1.f) return;
	
	ActiveSecond = 0.f;
	ReduceTime();
}

void ATimer::ReduceTime()
{
	SecondsRemaining--;
	
	SecondsRemaining = SecondsRemaining <= 0.f ? 0.f : SecondsRemaining;

	if (SecondsRemaining <= 0.f)
	{
		OnTimerEnd.Broadcast();
		
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("Timer Ended"));
	}
}

FString ATimer::SecondsToMinutes(float Seconds) // 72
{
	const float Remainder = static_cast<int32>(Seconds) % 60; // 12

	const float Minutes = (Seconds - Remainder)/*72-12=60*/ / 60.f >= 1.f ? (Seconds - Remainder) / 60.f : 0.f; // 1

	const FString LeadingZero = Remainder < 10 ? "0" : ""; // 12

	return FString(FString::FromInt(Minutes) + ":" + LeadingZero + FString::FromInt(Remainder)); // 1:12
}
