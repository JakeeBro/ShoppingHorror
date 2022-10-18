// Fill out your copyright notice in the Description page of Project Settings.


#include "SHPlayer.h"

// Sets default values
ASHPlayer::ASHPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(RootComponent);

	InteractionTracer = CreateDefaultSubobject<UInteractionTracer>(TEXT("Interaction Tracer"));
	InteractionTracer->DoTrace = true;

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

	ListTracker = CreateDefaultSubobject<UListTracker>(TEXT("List Tracker"));
}

// Called when the game starts or when spawned
void ASHPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASHPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASHPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Place", IE_Pressed, this, &ASHPlayer::Place);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASHPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASHPlayer::MoveRight);
	PlayerInputComponent->BindAxis("TurnRight", this, &ASHPlayer::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASHPlayer::LookUp);
}

void ASHPlayer::MoveForward(float Value)
{
	if (Controller == nullptr || Value  == 0.f) return;

	const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
	const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
	AddMovementInput(Direction, Value);
}

void ASHPlayer::MoveRight(float Value)
{
	if (Controller == nullptr || Value  == 0.f) return;

	const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
	const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
	AddMovementInput(Direction, Value);
}

void ASHPlayer::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASHPlayer::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ASHPlayer::Place()
{
	/*
	if (Inventory->ItemPropertiesMap.Num() <= 0) return;

	AItem* HeldItem = ListTracker->ActiveHeldItem;
	
	AItem* PlacedItem = GetWorld()->SpawnActorDeferred<AItem>(
		AItem::StaticClass(),
		GetActorTransform(),
		this,
		this,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

	PlacedItem->SetItemProperties(Inventory->ItemPropertiesMap.FindChecked(HeldItem));

	PlacedItem->FinishSpawning(GetActorTransform());

	const bool Clear = ListTracker->RemoveFromHeldList(HeldItem);

	Inventory->RemoveItem(HeldItem, Clear);
	*/
}

