// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArkanoidPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOver, int, FinalScore);

class ABall;
/**
 * 
 */
UCLASS()
class ARKANOID_API AArkanoidPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	
public:
	virtual void SetupInputComponent() override;
	
	void HandleHorizonalAxis(float HorizontalInput);

	void HandleLaunch();

	void StartInitialState();

	void DestroyBalls();

	UFUNCTION()
	void HandleDestroyedBall(ABall* Ball);

	UPROPERTY(BlueprintAssignable)
	FOnGameOver OnGameOver;

	void CreateAndLaunchBall();

private:
	UPROPERTY()
	ABall* HoldingBall;

	UPROPERTY()
	TArray<ABall*> Balls;

	bool GameOver = false;

	UPROPERTY()
	class AArkanoidGameModeBase* GameMode;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Ball")
	TSubclassOf<ABall> BallClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ball")
	FVector BallSpawnOffstet = FVector(0, 0, 20);
};
