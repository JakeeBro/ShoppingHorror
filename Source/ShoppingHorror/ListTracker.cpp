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

AItem* UListTracker::AddToHeldList(AItem* Item)
{
	TArray<AItem*> Keys;
	HeldList.GetKeys(Keys);

	if (Print)
	{
		// Keys Length Before Addition
		auto BeforeAddition = "Keys Before Addition: " + FString::FromInt(Keys.Num());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString(BeforeAddition));
	}

	// If the HeldList is Empty...
	if (Keys.Num() <= 0)
	{
		// Add a new Item with a Value of 1
		HeldList.Add(Item, 1);

		TArray<AItem*> HeldItems;
		HeldList.GetKeys(HeldItems);

		// Set the Newly Added Item as Active
		ActiveHeldItem = HeldItems[0];
	}
	else // If the HeldList is NOT Empty...
	{
		// Iterate through the Existing Keys
		for (AItem* I : Keys)
		{
			/*
			if (!IsValidChecked(I))
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("Invalid Item"));
				continue;
			}
			*/

			if (I->GetItemProperties().ItemName == Item->GetItemProperties().ItemName)
			{
				auto NewValue = HeldList.FindChecked(I) + 1;
				
				HeldList.Add(I, NewValue);

				if (Print)
				{
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, FString("Name Matched"));

					auto IncreaseHeldItem = "Item Already Held, Increasing Count: " + NewValue;
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString(IncreaseHeldItem));
				}
			}
			else
			{
				HeldList.Add(Item, 1);

				if (Print)
				{
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("Name Not Matched"));
				
					auto AddNewItem = "Item Not Held, Adding to List: " + 1;
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Turquoise, FString(AddNewItem));
				}
			}
		}
	}

	// Keys Length After Addition
	HeldList.GetKeys(Keys);

	if (Print)
	{
		auto AfterAddition = "Keys After Addition: " + FString::FromInt(Keys.Num());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(AfterAddition));
	}

	return Item;
}

bool UListTracker::RemoveFromHeldList(AItem* Item)
{
	if (Item == nullptr || HeldList.Num() <= 0) return false;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("REMOVE ENTERED"));

	if (HeldList.Num() <= 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString("HELD LIST LENGTH <= 1"));
		
		if (HeldList.FindChecked(Item) <= 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString("HELD ITEM AMOUNT <= 1"));
			
			HeldList.Reset();
			return true;
		}
		
		if (HeldList.FindChecked(Item) > 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString("HELD ITEM AMOUNT > 1"));
			
			auto Value = HeldList.FindChecked(Item) - 1;
			HeldList.Add(Item, Value);
			return false;
		}
	}

	if (HeldList.Num() > 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, FString("HELD LIST LENGTH > 1"));
		
		if (HeldList.FindChecked(Item) <= 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, FString("HELD ITEM AMOUNT <= 1"));
			
			TArray<AItem*> Items;
			HeldList.GetKeys(Items);
			
			HeldList.FindAndRemoveChecked(Item);
			HeldList.CompactStable();

			if (ActiveHeldIndex >= HeldList.Num())
			{
				ActiveHeldIndex = HeldList.Num() - 1;
				ActiveHeldItem = Items[ActiveHeldIndex];
			}
			
			return true;
		}
		
		if (HeldList.FindChecked(Item) > 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, FString("HELD ITEM AMOUNT > 1"));
			
			auto Value = HeldList.FindChecked(Item) - 1;
			HeldList.Add(Item, Value);
			return false;
		}
	}

	if (Print)
	{
		auto RemoveFromList = "Removing Item, New List Length: " + HeldList.Num();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString(RemoveFromList));
	}

	return false;
}

void UListTracker::UpdateActiveHeldIndex(float AxisValue)
{
	if (HeldList.Num() <= 1 || AxisValue == 0)
	{
		if (Print)
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Purple, FString("List Not Long Enough, or Scroll Wheel = 0, Scrolling Disabled"));
		return;
	}

	TArray<AItem*> HeldArray;
	HeldList.GetKeys(HeldArray);

	if (Print)
	{
		FString HeldArrayLength = "Held Array Length " + FString::FromInt(HeldArray.Num());
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, FString(HeldArrayLength));
	}
	
	if (AxisValue > 0)
	{
		if (ActiveHeldIndex + 1 == HeldList.Num())
			ActiveHeldIndex = 0;
		else
			ActiveHeldIndex++;

		if (Print)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, FString("POSITIVE SCROLL"));
		}
	}
	else if (AxisValue < 0)
	{
		if (ActiveHeldIndex == 0)
			ActiveHeldIndex = HeldList.Num() - 1;
		else
			ActiveHeldIndex--;

		if (Print)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, FString("NEGATIVE SCROLL"));
		}
	}

	if (Print)
	{
		auto HeldArrayItemName = "HeldArrayItemName = " + HeldArray[ActiveHeldIndex]->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Purple, FString(HeldArrayItemName));
	}

	ActiveHeldItem = HeldArray[ActiveHeldIndex]; // ERROR LINE

	if (Print)
	{
		auto HeldItemName = "Held Item = " + ActiveHeldItem->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString(HeldItemName));
	}
}

FString UListTracker::UpdateActiveHeldItemName()
{
	auto Path = GetPathNameSafe(ActiveHeldItem);

	FString Left;
	FString Right;
	
	Path.Split("BP_", &Left, &Right);
	Path = Right;
	Path.Split("_C", &Left, &Right);

	ActiveHeldItemName = Left;

	return Left;
}
