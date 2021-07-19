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

UCLASS()
class PILLAGE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	Class GetClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TEnumAsByte<Class> Class;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
