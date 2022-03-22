// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBrickDestroyed, class ABrick*, Brick);

UCLASS()
class ARKANOID_API ABrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrick();

	virtual void BeginPlay() override;
	
	int GetScore() { return 10 * BrickLevel; }
	
	void DamageBrick();

	UFUNCTION(BlueprintImplementableEvent)
	void DamageFeedback();

	UPROPERTY(BlueprintReadWrite)
	float TimeForDestroy = 0.1f;
	
	UPROPERTY(BlueprintAssignable)
	FOnBrickDestroyed OnBrickDestroyed;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int BrickLevel;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int BrickLife = 1;

	void SetLevel(int Level);

private:
	bool Destroying = false;
};
