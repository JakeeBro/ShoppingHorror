// Fill out your copyright notice in the Description page of Project Settings.

#include "ListManager.h"

AListManager::AListManager()
{

}

void AListManager::BeginPlay()
{
	Super::BeginPlay();
}

TMap<TSubclassOf<AItem>, int32> AListManager::WriteListClass()
{
	TMap<TSubclassOf<AItem>, int32> List;
	TArray<TSubclassOf<AItem>> ListItems;
	TArray<int32> ListItemAmounts;

	float SelectedDifficultyAmount;

	switch (ListDifficulty)
	{
		case EListDifficulty::Easy:
			SelectedDifficultyAmount = DifficultyAmount.Easy;
			break;
		case EListDifficulty::Normal:
			SelectedDifficultyAmount = DifficultyAmount.Normal;
			break;
		case EListDifficulty::Hard:
			SelectedDifficultyAmount = DifficultyAmount.Hard;
			break;
		default:
			SelectedDifficultyAmount = DifficultyAmount.Easy;
			break;
	}

	// If There aren't enough items implemented in the map, set the limit to the amount of items implemented
	if (SelectedDifficultyAmount > ItemIDClass.Num())
		SelectedDifficultyAmount = ItemIDClass.Num() - 1; // Subtract 1 Just to be Safe

	TArray<TSubclassOf<AItem>> ItemIDCopy = ItemIDClass;
	int32 IndexCache = 0;
	int32 LengthCache = ListItems.Num();

	while (ListItems.Num() < SelectedDifficultyAmount)
	{
		if (ItemIDCopy.Num() < 1) break;

		const float SelectedIndex = FMath::RandRange(0, ItemIDCopy.Num() - 1);

		if (SelectedIndex == IndexCache - 1 ? true : false)
			continue;
		
		IndexCache = SelectedIndex;
		
		if (ListItems.Num() == LengthCache)
		{
			ListItems.Add(ItemIDCopy[SelectedIndex]);
			LengthCache = ListItems.Num();
			ItemIDCopy.RemoveAt(SelectedIndex, 1, true);
		}
	}

	for (int i = 0; i < ListItems.Num(); i++)
	{
		ListItemAmounts.Add(FMath::RandRange(1, MaxAmountPerItem));
	}
	
	if (ListItems.Num() == ListItemAmounts.Num())
	{
		for (int i = 0; i < ListItems.Num(); i++)
		{
			List.Add(ListItems[i], ListItemAmounts[i]);
		}
	}
	
	return List;
}

TMap<FString, TSubclassOf<AItem>> AListManager::MapListToStrings(TMap<TSubclassOf<AItem>, int32> ClassList)
{
	TMap<FString, TSubclassOf<AItem>> Map;
	TArray<TSubclassOf<AItem>> ClassKeys;
	ClassList.GetKeys(ClassKeys);

	for (auto Class : ClassKeys)
	{
		auto Name = Class->GetDisplayNameText().ToString();

		FString Left;
		FString Right;
		Name.Split(TEXT("BP "), &Left, &Right);

		Map.Add(Right, Class);
	}

	return Map;
}
