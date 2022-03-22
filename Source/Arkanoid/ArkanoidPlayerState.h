// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ArkanoidPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLifeLost, int, RemainingLifes);

UCLASS()
class ARKANOID_API AArkanoidPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	int Life;
	
	UPROPERTY(BlueprintAssignable)
	FOnLifeLost OnLifeLost;

	UFUNCTION(BlueprintCallable)
	int GetInitialLife() const { return InitialLife; }
	
	void LoseLife();

	void GainLife();

protected:
	UPROPERTY(BlueprintReadWrite)	
	int InitialLife = 3;
};
