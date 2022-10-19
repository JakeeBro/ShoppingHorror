// Fill out your copyright notice in the Description page of Project Settings.

#include "ListTracker.h"

UListTracker::UListTracker()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UListTracker::BeginPlay()
{
	Super::BeginPlay();

}

void UListTracker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
