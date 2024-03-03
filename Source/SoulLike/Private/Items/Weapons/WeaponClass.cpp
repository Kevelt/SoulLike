// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WeaponClass.h"
#include "Characters/SoulLikeCharacter.h"

void AWeaponClass::OnBeginSphereCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginSphereCollisionOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeaponClass::OnEndSphereCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndSphereCollisionOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeaponClass::AttachMeshToSocket(USceneComponent* InParent, FName SocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	StaticMeshComponent->AttachToComponent(InParent, TransformRules, SocketName);
}