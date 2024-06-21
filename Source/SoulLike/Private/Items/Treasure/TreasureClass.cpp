// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Treasure/TreasureClass.h"
#include "Characters/SoulLikeCharacter.h"
#include "Kismet/GameplayStatics.h"

void ATreasureClass::OnBeginSphereCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASoulLikeCharacter* SoulLikeCharacter = Cast<ASoulLikeCharacter>(OtherActor);
	if (SoulLikeCharacter)
	{
		if (PickUpSound) {
			UGameplayStatics::PlaySoundAtLocation(this, PickUpSound, GetActorLocation());
		}
		Destroy();
	}
}
