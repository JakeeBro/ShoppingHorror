// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "ListManager.generated.h"

UENUM(BlueprintType)
enum class EListDifficulty : uint8
{
	Easy UMETA(FEnumDisplayNameFn="Easy"),
	Normal UMETA(FEnumDisplayNameFn="Normal"),
	Hard UMETA(FEnumDisplayNameFn="Hard")
};

USTRUCT(BlueprintType)
struct FDifficultyAmount
{
	GENERATED_BODY();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="List Manager")
	float Easy = 3.f;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="List Manager")
	float Normal = 6.f;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="List Manager")
	float Hard = 10.f;
};

UCLASS()
class SHOPPINGHORROR_API AListManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AListManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="List Manager")
	EListDifficulty ListDifficulty;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="List Manager")
	FDifficultyAmount DifficultyAmount;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="List Manager")
	TArray<TSubclassOf<AItem>> ItemIDClass;

	UFUNCTION(BlueprintCallable, Category="List Manager")
	TMap<TSubclassOf<AItem>, int32> WriteListClass();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="List Manager")
	int32 MaxAmountPerItem = 3.f;

	UFUNCTION(BlueprintCallable, Category="List Manager")
	TMap<FString, TSubclassOf<AItem>> MapListToStrings(TMap<TSubclassOf<AItem>, int32> ClassList);
	
public:	

};
