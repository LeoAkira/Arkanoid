// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveHelper.h"

#include "HighScoreSave.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

void USaveHelper::SaveHighScore(int NewHighScore)
{
	USaveGame* SaveGame = UGameplayStatics::LoadGameFromSlot(TEXT("HighScore"), 0);
	if (!SaveGame)
		SaveGame = UGameplayStatics::CreateSaveGameObject(UHighScoreSave::StaticClass());

	if (SaveGame)
	{
		if (UHighScoreSave* HighScoreSave = Cast<UHighScoreSave>(SaveGame))
		{
			HighScoreSave->HighScore = NewHighScore;
			UGameplayStatics::SaveGameToSlot(HighScoreSave, TEXT("HighScore"), 0);
		}
	}
}

int USaveHelper::LoadHighScore()
{
	if (USaveGame* SaveGame = UGameplayStatics::LoadGameFromSlot(TEXT("HighScore"), 0))
	{
		if (UHighScoreSave* HighScoreSave = Cast<UHighScoreSave>(SaveGame))
			return HighScoreSave->HighScore;
	}
	return 0;
}