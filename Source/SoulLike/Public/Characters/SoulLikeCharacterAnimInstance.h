// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SoulLikeCharacterTypes.h"
#include "SoulLikeCharacterAnimInstance.generated.h"

class ASoulLikeCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class SOULLIKE_API USoulLikeCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = Character)
	TObjectPtr<ASoulLikeCharacter> SoulLikeCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	TObjectPtr<UCharacterMovementComponent> SoulLikeCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float MoveSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool isFalling;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool isRunning;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement|Character State")
	ESoulLikeCharacterState SoulLikeCharacterState;
};
