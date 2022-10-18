// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UInventory::BeginPlay()
{
	Super::BeginPlay();

}

void UInventory::AddToInventory(AItem* Item, FItemProperties ItemProperties)
{
	if (Items.Contains(Item))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString("ADD TO INVENTORY: Item Found, Exiting"));\
		
		return;
	}
	if (Properties.Contains(ItemProperties))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString("ADD TO INVENTORY: Item Properties Found, Adding Value"));

		const auto Index = Properties.IndexOfByKey(ItemProperties);

		Values[Index] += 1;
		
		return;
	}

	Items.Add(Item);
	Properties.Add(ItemProperties);
	Values.Add(1);

	if (Items.Num() == 1)
	{
		ActiveItem = Properties[0];
	}
}

FItemProperties UInventory::RemoveFromInventory(FItemProperties ItemProperties)
{
	if (!Properties.Contains(ItemProperties)) return ItemProperties;

	const auto Index = Properties.IndexOfByKey(ItemProperties);

	if (Values[Index] > 1)
	{
		Values[Index]--;
	}
	else if (Values[Index] <= 1)
	{
		Items.RemoveAt(Index, 1, true);
		Properties.RemoveAt(Index, 1, true);
		Values.RemoveAt(Index, 1, true);

		if (ActiveIndex == Properties.Num() - 1)
			ActiveIndex = Properties.Num() - 2;
		if (ActiveIndex <= 0)
			ActiveIndex = 0;

		ActiveItem = Properties[ActiveIndex];
	}

	return ItemProperties;
}

void UInventory::UpdateActiveIndex(float AxisValue)
{
	if (Items.Num() <= 0 || AxisValue == 0)
	{
		if (Print)
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Purple, FString("Scroll Requirements Not Met"));
		return;
	}

	if (AxisValue < 0)
	{
		if (ActiveIndex + 1 == Items.Num())
			ActiveIndex = 0;
		else
			ActiveIndex++;
	}
	else if (AxisValue > 0)
	{
		if (ActiveIndex == 0)
			ActiveIndex = Items.Num() - 1;
		else
			ActiveIndex--;
	}

	ActiveItem = Properties[ActiveIndex];
}

void UInventory::AddItem(AItem* Item, FItemProperties ItemProperties)
{
	auto Key = ItemPropertiesMap.FindKey(ItemProperties);
	if (Key != nullptr) return;
	
	ItemPropertiesMap.Add(Item, ItemProperties);
}

void UInventory::RemoveItem(AItem* Item, bool Clear)
{
	if (ItemPropertiesMap.Num() <= 0) return;
	
	if (ItemPropertiesMap.Contains(Item) && Clear)
		ItemPropertiesMap.Remove(Item);
}
