// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SoulLikeCharacterTypes.h"
#include "SoulLikeCharacter.generated.h"

#pragma region UsedClass
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class ABaseItem;
class UAnimMontage;
class UAnimInstance;
class AWeaponClass;
#pragma endregion UsedClass

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

	FORCEINLINE bool GetIsRunning() const { return isRunning; }

	bool isMontageAnimationPlaying(const UAnimMontage* MontageAnimation);

	bool isAnyNotifyAnimationTriggered(const FName NotifyName);

	bool isAnyMontageAnimationPlaying();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToSockect(const FName SocketName);

#pragma region InputMappingAndAction
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

	UPROPERTY(EditAnywhere, Category = InputMapping)
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, Category = InputMapping)
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, Category = InputMapping)
	TObjectPtr<UInputAction> EquipUnequipWeaponAction;
#pragma endregion InputMappingAndAction

#pragma region InputEvents
	/*
	* Input Events
	*/
	void MoveForward(const FInputActionValue& Value);

	void LookAround(const FInputActionValue& Value);

	void EquipItem();

	void Attack();

	void RunForward();

	void StopRunForward();

	void EquipAndUnequipWeapon();

#pragma endregion InputEvents

#pragma region PlayMontagesEvent
	/*
	* Play Montages Event
	* 
	*/
	void PlayAttackMontage();

	void PlayEquipUnequipMontage(const FName SectionName);

#pragma endregion PlayMontagesEvent
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABaseItem> OverlappingItem;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
	TObjectPtr<AWeaponClass> EquippedWeapon;

	/* Animation Montages */

	UPROPERTY(EditDefaultsOnly, Category = Montage)
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
	TObjectPtr<UAnimMontage> EquipUnequipMontage;

	ESoulLikeCharacterState SoulLikeCharacterState = ESoulLikeCharacterState::ESCS_Unequipped;

	ESoulLikeCharacterActionState SoulLikeCharacterActionState = ESoulLikeCharacterActionState::ESCAS_Available;

	bool isRunning = false;

	UAnimInstance* GetAnimationInstance();
};
