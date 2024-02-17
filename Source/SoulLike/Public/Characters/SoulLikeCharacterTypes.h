#pragma once
UENUM(BlueprintType)
enum class ESoulLikeCharacterState : uint8
{
	ESCS_Unequipped UMETA(DisplayName = "Unequipped"),
	ESCS_EquippedOneHand UMETA(DisplayName = "Equipped One-Hand"),
};