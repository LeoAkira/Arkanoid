// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddle.h"

APlayerPaddle::APlayerPaddle()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentMovementDirection = ConsumeMovementInputVector();
	AddActorLocalOffset(CurrentMovementDirection * MovementSpeed * DeltaTime, true);
}
