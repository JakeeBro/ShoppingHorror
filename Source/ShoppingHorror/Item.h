// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

USTRUCT(BlueprintType)
struct FItemProperties
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Properties")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Properties")
	UStaticMesh* ItemMesh;

	bool operator== (const FItemProperties& Other) const
	{
		if (Other.ItemName == ItemName && Other.ItemMesh == ItemMesh)
			return true;

		return false;
	}
};

UCLASS()
class SHOPPINGHORROR_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

	UFUNCTION(BlueprintCallable, Category="Item")
	void SetItemProperties(FItemProperties Properties);

	UFUNCTION(BlueprintCallable, Category="Item")
	FItemProperties GetItemProperties();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(ExposeOnSpawn=true))
	FItemProperties ItemProperties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UStaticMeshComponent* Mesh;

public:	
	
};
