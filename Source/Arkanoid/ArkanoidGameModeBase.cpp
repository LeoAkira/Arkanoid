// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArkanoidGameModeBase.h"

#include "ArkanoidPlayerController.h"
#include "BrickManager.h"
#include "SaveHelper.h"
#include "Kismet/GameplayStatics.h"

AArkanoidGameModeBase::AArkanoidGameModeBase() : Super()
{
	BrickManager = CreateDefaultSubobject<UBrickManager>(TEXT("BrickManager"));
	CurrentRound = FirstRound;
}

void AArkanoidGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	BrickManager->SpawnBricks();
	BrickManager->OnAllBricksDestroyed.AddDynamic(this, &AArkanoidGameModeBase::OnAllBrickDestroyed);
	if (AArkanoidPlayerController* PlayerController = Cast<AArkanoidPlayerController>(GetWorld()->GetFirstPlayerController()))
		PlayerController->OnGameOver.AddDynamic(this, &AArkanoidGameModeBase::UpdateHighScore);
}

void AArkanoidGameModeBase::OnAllBrickDestroyed()
{
	StartRound();
}

void AArkanoidGameModeBase::StartRound()
{
	if (AArkanoidPlayerController* PlayerController = Cast<AArkanoidPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerController->DestroyBalls();
		CurrentRound++;
		
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, PlayerController]()
		{
			PlayerController->StartInitialState();
			BrickManager->SpawnBricks();
		}, TimeToStartRound, false);
	}
}

void AArkanoidGameModeBase::UpdateHighScore(int Score)
{
	if (USaveHelper::LoadHighScore() < Score)
	{
		USaveHelper::SaveHighScore(Score);
	}
}
