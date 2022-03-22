// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveHelper.generated.h"

/**
 * 
 */
UCLASS()
class ARKANOID_API USaveHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void SaveHighScore(int NewHighScore);

	UFUNCTION(BlueprintCallable)
	static int LoadHighScore();
};
