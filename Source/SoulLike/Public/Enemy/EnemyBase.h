// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "EnemyBase.generated.h"

#pragma region UsedClass
class UAnimMontage;
class USoundBase;
class UParticleSystem;
#pragma endregion UsedClass

UCLASS()
class SOULLIKE_API AEnemyBase : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit_Implementation(const FVector& HitImpact) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region PlayMontagesEvent
	/*
	* Play Montages Event
	*/
	void PlayHitMontage();

#pragma endregion PlayMontagesEvent

private:
	/* Animation Montages */

	UPROPERTY(EditDefaultsOnly, Category = Montage)
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, Category = Sounds)
	TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	TObjectPtr<UParticleSystem> HitParticle;

};
