#pragma once
UENUM(BlueprintType)
enum class ESoulLikeCharacterState : uint8
{
	ESCS_Unequipped UMETA(DisplayName = "Unequipped"),
	ESCS_EquippedOneHand UMETA(DisplayName = "Equipped One-Hand"),
};

UENUM(BlueprintType)
enum class ESoulLikeCharacterActionState : uint8
{
	ESCAS_Available UMETA(DisplayName = "Available"),
	ESCAS_Occupied UMETA(DisplayName = "Occupied")
};