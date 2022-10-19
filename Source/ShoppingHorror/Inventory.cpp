// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;

	NullItemProperties.ItemName = "";
	NullItemProperties.ItemMesh = nullptr;
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();

}

void UInventory::AddToInventory(AItem* Item, FItemProperties ItemProperties)
{
	if (ItemClasses.Contains(Item->GetClass()))
	{
		if (Print)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString("ADD TO INVENTORY: Item Class Found, Adding Value"));

		const auto Index = Properties.IndexOfByKey(ItemProperties);

		Values[Index] += 1;
		
		return;
	}

	if (Print)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString("ADD TO INVENTORY: Item Properties Not Found, Adding Item"));

	ItemClasses.Add(Item->GetClass());
	Properties.Add(ItemProperties);
	Values.Add(1);

	if (ItemClasses.Num() == 1)
	{
		ActiveItem = Properties[0];
	}
}

FItemProperties UInventory::RemoveFromInventory(FItemProperties ItemProperties, bool& Continue)
{
	Continue = true;
	
	if (!Properties.Contains(ItemProperties))
	{
		if (Print)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString("REMOVE FROM INVENTORY: Given Properties Not Found in Array"));
		Continue = false;
		return NullItemProperties;
	}

	const auto Index = Properties.IndexOfByKey(ItemProperties);

	if (Values[Index] > 1)
	{
		Values[Index]--;
	}
	else if (Values[Index] <= 1)
	{
		if (ActiveIndex == Properties.Num() - 1)
			ActiveIndex = Properties.Num() - 2;
		if (ActiveIndex <= 0)
			ActiveIndex = 0;

		if (Print)
		{
			FString Class = "Class: " + ItemClasses[Index]->GetName() + " // ";
			FString PropertyName = "Item Name: " + Properties[Index].ItemName + " // ";
			FString PropertyMesh = "Item Mesh: " + Properties[Index].ItemMesh->GetName() + " // ";
			FString Value = "Value: " + FString::FromInt(Values[Index]);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString("REMOVING: " + Class + PropertyName + PropertyMesh + Value));
		}

		ItemClasses.RemoveAt(Index, 1, true);
		Properties.RemoveAt(Index, 1, true);
		Values.RemoveAt(Index, 1, true);

		if (Properties.Num() >= 1)
			ActiveItem = Properties[ActiveIndex];
		else
			ActiveItem = NullItemProperties;
	}

	return ItemProperties;
}

void UInventory::ReadActiveIndex(TSubclassOf<AItem>& IndexClass, FItemProperties& IndexProperties, int32& IndexValue)
{
	if (ItemClasses.Num() <= 0) return;
	
	IndexClass = ItemClasses[ActiveIndex];
	IndexProperties = Properties[ActiveIndex];
	IndexValue = Values[ActiveIndex];
}

void UInventory::UpdateActiveIndex(float AxisValue)
{
	if (ItemClasses.Num() <= 0 || AxisValue == 0)
	{
		if (Print)
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Purple, FString("UPDATE ACTIVE INDEX: Scroll Requirements Not Met"));
		return;
	}

	if (AxisValue < 0)
	{
		if (ActiveIndex + 1 == ItemClasses.Num())
			ActiveIndex = 0;
		else
			ActiveIndex++;
	}
	else if (AxisValue > 0)
	{
		if (ActiveIndex == 0)
			ActiveIndex = ItemClasses.Num() - 1;
		else
			ActiveIndex--;
	}

	ActiveItem = Properties[ActiveIndex];
}
