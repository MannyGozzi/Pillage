// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "Weapon.h"
#include "ItemInteractor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PILLAGE_API UItemInteractor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemInteractor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(ReplicatedUsing = OnRep_FoundWeapon)
	AWeapon* FoundWeapon;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_FindItems();

private:
	const float REACH = 100.f;
	const uint32 WeaponLimit = 2;
	
	UPROPERTY()
	TArray<AWeapon*> Weapons;

	UPROPERTY()
	TArray<AItem*> Items;

	UFUNCTION(Server, Reliable)
	void Server_ItemFound(AItem* Item);

	void WeaponFound(AWeapon* Weapon);
	UFUNCTION()
	void AddWeaponToInventory(AWeapon* Weapon);
	UFUNCTION()
	void OnRep_FoundWeapon();
};
