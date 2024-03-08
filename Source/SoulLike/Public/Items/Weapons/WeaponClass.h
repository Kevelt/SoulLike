// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "WeaponClass.generated.h"

class UBoxComponent;
class USceneComponent;
/**
 * 
 */
UCLASS()
class SOULLIKE_API AWeaponClass : public ABaseItem
{
	GENERATED_BODY()

public:
	AWeaponClass();

	void AttachMeshToSocket(USceneComponent* InParent, FName SocketName);

protected:
	virtual void BeginPlay() override;

	virtual void OnBeginSphereCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnEndSphereCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	void OnBeginBoxCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	TObjectPtr<UBoxComponent> WeaponBoxComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Trace")
	TObjectPtr<USceneComponent> BoxTraceCollisionStart;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Trace")
	TObjectPtr<USceneComponent> BoxTraceCollisionEnd;
	
};
