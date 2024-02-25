// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SoulLikeCharacterAnimInstance.h"
#include "Characters/SoulLikeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USoulLikeCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	SoulLikeCharacter = Cast<ASoulLikeCharacter>(TryGetPawnOwner());
	if (SoulLikeCharacter)
	{
		SoulLikeCharacterMovement = SoulLikeCharacter->GetCharacterMovement();
	}
}

void USoulLikeCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (SoulLikeCharacterMovement)
	{
		MoveSpeed = UKismetMathLibrary::VSizeXY(SoulLikeCharacterMovement->Velocity);
		isFalling = SoulLikeCharacterMovement->IsFalling();
		isRunning = SoulLikeCharacter->GetIsRunning();
		SoulLikeCharacterState = SoulLikeCharacter->GetSoulLikeCharacterState();
	}
}
