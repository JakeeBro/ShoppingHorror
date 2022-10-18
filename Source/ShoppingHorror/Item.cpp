// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	// ItemProperties.ItemName = 
}

void AItem::SetItemProperties(FItemProperties Properties)
{
	ItemProperties = Properties;
}

FItemProperties AItem::GetItemProperties()
{
	return ItemProperties;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	if (ItemProperties.ItemMesh)
		Mesh->SetStaticMesh(ItemProperties.ItemMesh);
	
}

