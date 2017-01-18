// hexode.xyz

#pragma once

/**
 * 
 */
UENUM(BlueprintType)
enum class EOrientationEnum : uint8
{
	O_NORTH			UMETA(DisplayName = "NORTH"),
	O_NORTH_EAST	UMETA(DisplayName = "NORTH_EAST"),
	O_SOUTH_EAST	UMETA(DisplayName = "SOUTH_EAST"),
	O_SOUTH			UMETA(DisplayName = "SOUTH"),
	O_SOUTH_WEST	UMETA(DisplayName = "SOUTH_WEST"),
	O_NORTH_WEST	UMETA(DisplayName = "NORTH_WEST")
};
