// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "TreasureClass.generated.h"

#pragma region UsedClass
class USoundBase;
#pragma endregion UsedClass

/**
 * 
 */
UCLASS()
class SOULLIKE_API ATreasureClass : public ABaseItem
{
	GENERATED_BODY()
	
protected:
	virtual void OnBeginSphereCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditAnywhere, Category = Sounds)
	TObjectPtr<USoundBase> PickUpSound;

	UPROPERTY(EditAnywhere, Category = TreasureProperties)
	int32 GoldAmount;
};
