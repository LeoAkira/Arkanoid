// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidPlayerState.h"

void AArkanoidPlayerState::BeginPlay()
{
	Super::BeginPlay();

	Life = InitialLife;
}

void AArkanoidPlayerState::LoseLife()
{
	Life--;
	OnLifeLost.Broadcast(Life);
}

void AArkanoidPlayerState::GainLife()
{
	Life++;
	OnLifeLost.Broadcast(Life);
}
