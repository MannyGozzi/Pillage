// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM()
enum Class
{
	Weapon		UMETA(DisplayName = "Weapon"),
	Consumeable	UMETA(DisplayName = "Consumeable"),
	Resource	UMETA(DisplayName = "Resource")
};

UENUM()
enum ItemName
{
	Axe					UMETA(DisplayName = "Axe"),
	Crossbow			UMETA(DisplayName = "Crossbow"),
	Sword				UMETA(DisplayName = "Sword"),
	Staff				UMETA(DisplayName = "Staff"),

	PotionSpeed			UMETA(DisplayName = "PotionSpeed"),
	PotionFireSpeed		UMETA(DisplayName = "PotionFireSpeed"),
	PotionDamage		UMETA(DisplayName = "PotionDamage"),

	CrateWood			UMETA(DisplayName = "CrateWood"),
	CrateMetal			UMETA(DisplayName = "CrateMetal"),
};

UCLASS()
class PILLAGE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	Class GetClass();
	FString GetItemNameString();
	ItemName GetItemName();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<Class> Class;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ItemName> ItemName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UClass* GetItemStaticClass();

};
