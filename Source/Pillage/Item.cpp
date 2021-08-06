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

Class AItem::GetClass()
{
	return Class;
}

FString AItem::GetItemNameString()
{
	switch (ItemName)
	{
	case Axe:
		return TEXT("Axe");
		break;
	case Sword:
		return TEXT("Sword");
		break;
	case Crossbow:
		return TEXT("Crossbow");
		break;
	case Staff:
		return TEXT("Staff");
		break;
	case PotionSpeed:
		return TEXT("PotionSpeed");
		break;
	case PotionFireSpeed:
		return TEXT("PotionFireSpeed");
		break;
	case PotionDamage:
		return TEXT("PotionDamage");
		break;
	case CrateWood:
		return TEXT("CrateWood");
		break;
	case CrateMetal:
		return TEXT("CrateMetal");
		break;
	default:
		return TEXT("None");
		break;
	}
}

ItemName AItem::GetItemName()
{
	return ItemName;
}

UClass* AItem::GetItemStaticClass()
{
	return StaticClass();
}
