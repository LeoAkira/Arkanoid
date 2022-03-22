// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"

ABrick::ABrick()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABrick::BeginPlay()
{
	Super::BeginPlay();
}

void ABrick::DamageBrick()
{
	BrickLife--;
	DamageFeedback();
	
	if (BrickLife <= 0 && !Destroying)
	{
		OnBrickDestroyed.Broadcast(this);
		if (TimeForDestroy > 0) SetLifeSpan(TimeForDestroy);
		else Destroy();
		Destroying = true;
	}
}

void ABrick::SetLevel(int Level)
{
	BrickLevel = Level;
	BrickLife = Level;
	DamageFeedback();
}

