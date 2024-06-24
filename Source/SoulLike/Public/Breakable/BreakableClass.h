// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/HitInterface.h"
#include "GameFramework/Actor.h"
#include "BreakableClass.generated.h"

class UGeometryCollectionComponent;
class ATreasureClass;
class UCapsuleComponent;

UCLASS()
class SOULLIKE_API ABreakableClass : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	
	ABreakableClass();
	virtual void Tick(float DeltaTime) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UGeometryCollectionComponent> GeometryCollection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

private:
	UPROPERTY(EditAnywhere, Category = BreakProperties)
	TArray<TSubclassOf<ATreasureClass>> TreasureClassList;
};
