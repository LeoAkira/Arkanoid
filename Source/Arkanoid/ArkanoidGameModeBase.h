// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArkanoidGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARKANOID_API AArkanoidGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	AArkanoidGameModeBase();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnAllBrickDestroyed();

	UFUNCTION()
	void StartRound();
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBrickManager* BrickManager;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float TimeToStartRound;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int FirstRound = 0;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float DefaultSpeed = 400;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float SpeedRoundIncrease = 25;

	UFUNCTION(BlueprintImplementableEvent)
	void WinFeedback();

	int CurrentRound;

	float GetRoundSpeed() const { return DefaultSpeed + SpeedRoundIncrease * CurrentRound;}

	UFUNCTION()
	void UpdateHighScore(int Score);
};
