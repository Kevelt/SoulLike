// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SoulLikeCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Items/BaseItem.h"
#include "Items/Weapons/WeaponClass.h"
#include "Animation/AnimMontage.h"

// Sets default values
ASoulLikeCharacter::ASoulLikeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 450.0f, 0.0f); // ...at this rotation rate

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

}

bool ASoulLikeCharacter::isMontageAnimationPlaying(const UAnimMontage* MontageAnimation)
{
	bool bIsActiveMontage = false;
	if (GetAnimationInstance()) {
		bIsActiveMontage = GetAnimationInstance()->Montage_GetIsStopped(MontageAnimation);
	}
	return bIsActiveMontage;
}

bool ASoulLikeCharacter::isAnyMontageAnimationPlaying()
{
	bool bIsAnyActiveMontage = false;
	if (GetAnimationInstance()) {
		bIsAnyActiveMontage = GetAnimationInstance()->IsAnyMontagePlaying();
	}
	return bIsAnyActiveMontage;
}

bool ASoulLikeCharacter::isAnyNotifyAnimationTriggered(const FName NotifyName)
{
	return GetAnimationInstance()->WasAnimNotifyNameTriggeredInAnyState(NotifyName);
}

UAnimInstance* ASoulLikeCharacter::GetAnimationInstance()
{
	UAnimInstance* AnimationInstance = GetMesh()->GetAnimInstance();
	return AnimationInstance;
}

// Called when the game starts or when spawned
void ASoulLikeCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(SoulLikeCharacterMappingContext, 0);
		}
	}
	
}

void ASoulLikeCharacter::MoveForward(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (isAnyMontageAnimationPlaying()) return;

	if (GetController())
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASoulLikeCharacter::LookAround(const FInputActionValue& Value)
{
	if (isAnyMontageAnimationPlaying()) return;
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (GetController())
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASoulLikeCharacter::EquipItem()
{
	AWeaponClass* OverlappingWeaponItem = Cast<AWeaponClass>(OverlappingItem);
	if (OverlappingWeaponItem)
	{
		OverlappingWeaponItem->AttachMeshToSocket(GetMesh(), FName("hand_lSocket"));
		SoulLikeCharacterState = ESoulLikeCharacterState::ESCS_EquippedOneHand;
		EquippedWeapon = OverlappingWeaponItem;
	}
}

void ASoulLikeCharacter::Attack()
{
	const bool bCanAttack = SoulLikeCharacterState != ESoulLikeCharacterState::ESCS_Unequipped;
	if (bCanAttack)
	{
		PlayAttackMontage();
	}
}

void ASoulLikeCharacter::RunForward()
{
	if (GetCharacterMovement())
	{
		isRunning = true;
		GetCharacterMovement()->MaxWalkSpeed = 380.f;
	}
}

void ASoulLikeCharacter::StopRunForward()
{
	if (GetCharacterMovement())
	{
		isRunning = false;
		GetCharacterMovement()->MaxWalkSpeed = 100.f;
	}
}

void ASoulLikeCharacter::EquipAndUnequipWeapon()
{
	if (!isRunning && SoulLikeCharacterState == ESoulLikeCharacterState::ESCS_Unequipped && EquippedWeapon && !isAnyMontageAnimationPlaying())
	{
		PlayEquipUnequipMontage(FName("Equip"));
		SoulLikeCharacterState = ESoulLikeCharacterState::ESCS_EquippedOneHand;
	}
	else if (!isRunning && SoulLikeCharacterState == ESoulLikeCharacterState::ESCS_EquippedOneHand && EquippedWeapon && !isAnyMontageAnimationPlaying())
	{
		PlayEquipUnequipMontage(FName("Unequip"));
		SoulLikeCharacterState = ESoulLikeCharacterState::ESCS_Unequipped;
	}
}

void ASoulLikeCharacter::PlayEquipUnequipMontage(FName SectionName)
{
	if (GetAnimationInstance() && EquipUnequipMontage)
	{
		GetAnimationInstance()->Montage_Play(EquipUnequipMontage);
		GetAnimationInstance()->Montage_JumpToSection(SectionName, EquipUnequipMontage);
	}
}

void ASoulLikeCharacter::AttachWeaponToSockect(FName SocketName)
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), SocketName);
	}
}

void ASoulLikeCharacter::PlayAttackMontage()
{
	if (GetAnimationInstance() && AttackMontage && isMontageAnimationPlaying(AttackMontage))
	{
		GetAnimationInstance()->Montage_Play(AttackMontage);
		const int32 RandomSelection = FMath::RandRange(0, 1);
		FName SectionName = FName();
		switch (RandomSelection)
		{
		case 0:
			SectionName = FName("Attack1");
			break;
		case 1:
			SectionName = FName("Attack2");
			break;
		default:
			SectionName = FName("Attack1");
			break;
		}
		GetAnimationInstance()->Montage_JumpToSection(SectionName, AttackMontage);
	}
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

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASoulLikeCharacter::MoveForward);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASoulLikeCharacter::LookAround);

		//Equiping
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &ASoulLikeCharacter::EquipItem);

		//Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASoulLikeCharacter::Attack);

		//RunForward
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ASoulLikeCharacter::RunForward);

		//StopRunForward
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ASoulLikeCharacter::StopRunForward);

		//EquipAndUnequipWeapon
		EnhancedInputComponent->BindAction(EquipUnequipWeaponAction, ETriggerEvent::Started, this, &ASoulLikeCharacter::EquipAndUnequipWeapon);
	}

}

