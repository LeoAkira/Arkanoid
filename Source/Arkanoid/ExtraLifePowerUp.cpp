// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtraLifePowerUp.h"

#include "ArkanoidPlayerController.h"
#include "ArkanoidPlayerState.h"

void AExtraLifePowerUp::UsePowerUp()
{
	Super::UsePowerUp();

	if (AArkanoidPlayerController* PlayerController = Cast<AArkanoidPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (AArkanoidPlayerState* ArkanoidPlayerState = Cast<AArkanoidPlayerState>(PlayerController->PlayerState))
		{
			ArkanoidPlayerState->GainLife();
		}
	}
}
