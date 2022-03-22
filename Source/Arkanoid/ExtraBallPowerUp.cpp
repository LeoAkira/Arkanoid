// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtraBallPowerUp.h"

#include "ArkanoidPlayerController.h"

void AExtraBallPowerUp::UsePowerUp()
{
	Super::UsePowerUp();

	if (AArkanoidPlayerController* PlayerController = Cast<AArkanoidPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerController->CreateAndLaunchBall();
	}
}
