// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SoulLikeCharacter.h"

// Sets default values
ASoulLikeCharacter::ASoulLikeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoulLikeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoulLikeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASoulLikeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

