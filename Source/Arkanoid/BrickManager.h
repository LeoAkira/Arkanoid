// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArkanoidGameModeBase.h"
#include "BasePowerUp.h"
#include "Brick.h"
#include "Components/ActorComponent.h"
#include "BrickManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllBricksDestroyed);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARKANOID_API UBrickManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UBrickManager();

	virtual void BeginPlay() override;
	
	void SpawnBricks();

	UFUNCTION()
	void HandleBrickDestroyed(ABrick* Brick);
	
private:
	FVector GetPositionFor(int Row, int Column);

	UPROPERTY()
	AArkanoidGameModeBase* GameMode;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Level")
	int NumRows;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Level")
	int NumColumns;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TSubclassOf<ABrick> BrickClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Level")
	FVector SpawnStart;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Level")
	FVector SpawnEnd;

	UPROPERTY(BlueprintAssignable, Category="Default")
	FOnAllBricksDestroyed OnAllBricksDestroyed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	int MaxBrickLevels = 4;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Level")
	int MaxRows = 10;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Level")
	int MaxColumns = 20;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="PowerUps")
	TArray<TSubclassOf<ABasePowerUp>> PowerUps;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="PowerUps")
	float PowerUpSpawnChance = 0.1f;
	
	int GetRound() const { return GameMode->CurrentRound; }
	
private:
	float BrickWidth;
	float BrickHeight;
	int RemainingBricks;
};
