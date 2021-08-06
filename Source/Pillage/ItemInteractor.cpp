// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInteractor.h"
#include "PillageCharacter.h"
#include "Weapon.h"
#include "Item.h"
#include "Kismet/KismetSystemLibrary.h" 

// Sets default values for this component's properties
UItemInteractor::UItemInteractor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UItemInteractor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UItemInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UItemInteractor::FindItems()
{
	if (GetOwner() == nullptr) return false;
	APillageCharacter* Owner = Cast<APillageCharacter>(GetOwner());
	if (Owner == nullptr) return false;
	const FVector Location = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * REACH;
	TArray<AActor*> ActorsToIgnore;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	// https://skookum.chat/t/eobjecttypequery-is-difficult-to-work-with/795
	// ObjectTypeQuery1 is defined as WorldDynamic objects
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
	ActorsToIgnore.Add(GetOwner());
	ActorsToIgnore.Add(Cast<AActor>(Owner->GetCurrentWeapon()));
	TArray<AActor*> FoundItems;

	const bool ObjectFound = UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(), Location, REACH,
		ObjectTypes, AItem::StaticClass(), ActorsToIgnore, FoundItems
	);

	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Location, REACH, 16, FLinearColor::White, 1.f, 1.f );

	if (ObjectFound)
	{
		for (AActor* Item: FoundItems)
		{
			if (GEngine == nullptr) return false;
			if (Item == nullptr) return false;
			GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Orange, FString::Printf(TEXT("Hit %s"), *Item->GetName()));
			AItem* FoundItem = Cast<AItem>(Item);
			if (FoundItem == nullptr) continue;
			ItemFound(FoundItem);
			break;
		}
	}
	return ObjectFound;
}

void UItemInteractor::ItemFound(AItem* Item)
{
	Class ItemClass = Item->GetClass();
	switch (ItemClass)
	{
	case Class::Weapon:
	{
		AWeapon* Weapon = Cast<AWeapon>(Item);
		if (Weapon != nullptr) WeaponFound(Weapon);
		break;
	}
	case Class::Consumeable:
	{
		UE_LOG(LogTemp, Warning, TEXT("Found consumeable"));
		break;
	}
	case Class::Resource:
	{
		UE_LOG(LogTemp, Warning, TEXT("Found resource"));
		break;
	}
	default:
		break;
	}
}

void UItemInteractor::WeaponFound(AWeapon* Weapon)
{
	UE_LOG(LogTemp, Warning, TEXT("Found Weapon: %s"), *Weapon->GetItemNameString());
	if (Weapons.Num() > (int32) WeaponLimit) return;
	AddWeaponToInventory(Weapon);
}

void UItemInteractor::AddWeaponToInventory(AWeapon* Weapon)
{
	Weapons.Add(Weapon);
	UE_LOG(LogTemp, Warning, TEXT("Added %s to weapon inventory"), *Weapon->GetItemNameString());
	UE_LOG(LogTemp, Warning, TEXT("Equipping weapon"));
	if (GetOwner() == nullptr) return;
	APillageCharacter* Owner = Cast<APillageCharacter>(GetOwner());
	if (Owner == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("Owner found, adding weapon"));
	Owner->SetCurrentWeapon(Weapon);
}

