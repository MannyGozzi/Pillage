// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EClass AItem::GetClass()
{
	return Class;
}

FString AItem::GetItemNameString()
{
	switch (ItemName)
	{
	case EItemName::Axe:
		return TEXT("Axe");
		break;
	case EItemName::Sword:
		return TEXT("Sword");
		break;
	case EItemName::Crossbow:
		return TEXT("Crossbow");
		break;
	case EItemName::Staff:
		return TEXT("Staff");
		break;
	case EItemName::PotionSpeed:
		return TEXT("PotionSpeed");
		break;
	case EItemName::PotionFireSpeed:
		return TEXT("PotionFireSpeed");
		break;
	case EItemName::PotionDamage:
		return TEXT("PotionDamage");
		break;
	case EItemName::CrateWood:
		return TEXT("CrateWood");
		break;
	case EItemName::CrateMetal:
		return TEXT("CrateMetal");
		break;
	default:
		return TEXT("None");
		break;
	}
}

EItemName AItem::GetItemName()
{
	return ItemName;
}