// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePowerUp.h"
#include "ExtraLifePowerUp.generated.h"

/**
 * 
 */
UCLASS()
class ARKANOID_API AExtraLifePowerUp : public ABasePowerUp
{
	GENERATED_BODY()

	virtual void UsePowerUp() override;
};
