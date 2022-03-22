// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePowerUp.h"
#include "ExtraBallPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class ARKANOID_API AExtraBallPowerUp : public ABasePowerUp
{
	GENERATED_BODY()

	virtual void UsePowerUp() override;
};
