// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickManager.h"

#include "ArkanoidGameModeBase.h"
#include "BasePowerUp.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UBrickManager::UBrickManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBrickManager::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AArkanoidGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}


FVector UBrickManager::GetPositionFor(int Row, int Column)
{
	if (Row >= 0 && Row < (NumRows + GetRound()) && Column >= 0 && Column < (NumColumns + 2 * GetRound()))
	{
		float XPos = SpawnStart.X + BrickWidth / 2 + Column * BrickWidth;
		float ZPos = SpawnStart.Z + BrickHeight / 2 + Row * BrickHeight;
		return FVector(XPos, 0, ZPos);
	}
	return FVector::ZeroVector;
}

void UBrickManager::SpawnBricks()
{
	int RoundColumns = UKismetMathLibrary::Min(NumColumns + 2 * GetRound(), MaxColumns);
	int RoundRows = UKismetMathLibrary::Min(NumRows + GetRound(), MaxRows);
	RemainingBricks = RoundColumns * RoundRows;
	BrickWidth = UKismetMathLibrary::Abs(SpawnEnd.X - SpawnStart.X) / RoundColumns;
	BrickHeight = UKismetMathLibrary::Abs(SpawnEnd.Z - SpawnStart.Z) / RoundRows;
	
	FVector BrickScale = FVector::ZeroVector;
	int FirstRow = UKismetMathLibrary::Max(1, NumRows + GetRound() - (MaxBrickLevels - 1) * 2 - 1);
	for (int Row = 0; Row < RoundRows; Row++)
	{
		int RowLevel = UKismetMathLibrary::Min(FirstRow + Row / 2, MaxBrickLevels);
		for (int Column = 0; Column < RoundColumns; Column++)
		{
			if (ABrick* MyBrick = GetWorld()->SpawnActor<ABrick>(BrickClass))
			{
				MyBrick->SetActorLocation(GetPositionFor(Row, Column));
				if (BrickScale.IsZero())
				{
					FVector DefaultBrickSize, Origin;
					MyBrick->GetActorBounds(false, Origin, DefaultBrickSize, true);
					BrickScale = FVector(BrickWidth / (DefaultBrickSize.X * 2), BrickHeight / (DefaultBrickSize.Z * 2), 1);
				}
				MyBrick->SetActorScale3D(BrickScale);
				MyBrick->OnBrickDestroyed.AddDynamic(this, &UBrickManager::HandleBrickDestroyed);
				MyBrick->SetLevel(RowLevel);
			}
		}
	}
}

void UBrickManager::HandleBrickDestroyed(ABrick* Brick)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->PlayerState->SetScore(PlayerController->PlayerState->GetScore() + Brick->GetScore());
	}
	RemainingBricks--;
	if (RemainingBricks <= 0) OnAllBricksDestroyed.Broadcast();
	else
	{
		if (PowerUpSpawnChance * Brick->BrickLevel > FMath::FRand())
		{
			int PowerUpId = FMath::RandRange(0, PowerUps.Num() - 1);
			ABasePowerUp* PowerUp = GetWorld()->SpawnActor<ABasePowerUp>(PowerUps[PowerUpId]);
			PowerUp->SetActorLocation(Brick->GetActorLocation());
		}
	}
}

