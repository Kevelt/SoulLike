// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SoulLikeCharacterTypes.h"
#include "SoulLikeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class ABaseItem;


UCLASS()
class SOULLIKE_API ASoulLikeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASoulLikeCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void SetOverlappingItem(ABaseItem* ItemOverlap) { OverlappingItem = ItemOverlap; }

	FORCEINLINE ESoulLikeCharacterState GetSoulLikeCharacterState() const { return SoulLikeCharacterState; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = InputMapping)
	TObjectPtr<UInputMappingContext> SoulLikeCharacterMappingContext;

	UPROPERTY(EditAnywhere, Category = InputMapping)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = InputMapping)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = InputMapping)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = InputMapping)
	TObjectPtr<UInputAction> EquipAction;

	void MoveForward(const FInputActionValue& Value);

	void LookAround(const FInputActionValue& Value);

	void EquipItem();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABaseItem> OverlappingItem;

	ESoulLikeCharacterState SoulLikeCharacterState = ESoulLikeCharacterState::ESCS_Unequipped;
};
