// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInteractor.h"
#include "PillageCharacter.h"
#include "Weapon.h"
#include "Item.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UItemInteractor::UItemInteractor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
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

void UItemInteractor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UItemInteractor, FoundWeapon);
}

void UItemInteractor::Server_FindItems_Implementation()
{
	if (!GetOwner()) return;
	APillageCharacter* Owner = Cast<APillageCharacter>(GetOwner());
	if (Owner == nullptr) return;
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

	//UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Location, REACH, 16, FLinearColor::White, 1.f, 1.f );

	if (ObjectFound)
	{
		for (AActor* Item: FoundItems)
		{
			if (!GEngine) return;
			if (!Item) return;
			GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Orange, FString::Printf(TEXT("Hit %s"), *Item->GetName()));
			AItem* FoundItem = Cast<AItem>(Item);
			if (!FoundItem || FoundItem->IsItemEquipped()) continue;
			Server_ItemFound(FoundItem);
			break;
		}
	}
}

bool UItemInteractor::Server_FindItems_Validate()
{
	return true;
}

void UItemInteractor::Server_ItemFound_Implementation(AItem* Item)
{
	EClass ItemClass = Item->GetClass();
	switch (ItemClass)
	{
	case EClass::Weapon:
	{
		AWeapon* Weapon = Cast<AWeapon>(Item);
		if (Weapon != nullptr) WeaponFound(Weapon);
		break;
	}
	case EClass::Consumeable:
	{
		UE_LOG(LogTemp, Warning, TEXT("Found consumeable"));
		break;
	}
	case EClass::Resource:
	{
		UE_LOG(LogTemp, Warning, TEXT("Found resource"));
		break;
	}
	default:
		break;
	}
}


void UItemInteractor::AddWeaponToInventory(AWeapon* Weapon)
{
	UE_LOG(LogTemp, Warning, TEXT("Added %s to weapon inventory"), *Weapon->GetItemNameString());
	Weapons.Emplace(Weapon);
	if (!GetOwner()) return;
	APillageCharacter* Owner = Cast<APillageCharacter>(GetOwner());
	if (Owner == nullptr) return;
	
	Owner->SetCurrentWeapon(Weapon);
}

void UItemInteractor::OnRep_FoundWeapon()
{
	WeaponFound(FoundWeapon);
}

void UItemInteractor::WeaponFound(AWeapon* Weapon)
{
	if ((uint32)Weapons.Num() >= WeaponLimit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Maximum number of items attained: WeaponLimit = (%d)"), WeaponLimit);
		return;
	}
	Weapon->ItemEquipped();
	FoundWeapon = Weapon;
	AddWeaponToInventory(Weapon);
}