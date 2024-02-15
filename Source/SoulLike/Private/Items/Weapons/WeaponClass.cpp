// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WeaponClass.h"

void AWeaponClass::OnBeginSphereCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginSphereCollisionOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeaponClass::OnEndSphereCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndSphereCollisionOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
