// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/BNGameMusicAudioComponent.h"

#include <Sound/SoundCue.h>

void UBNGameMusicAudioComponent::PlayGameMusic(FGameplayTag GameMusicGameplayTag)
{
    if (ensure(GameMusicDataTable))
	{
		TArray<FBNGameMusicTableInfoRow*> GameMusicTableRows;
		GameMusicDataTable->GetAllRows("", GameMusicTableRows);

		for (FBNGameMusicTableInfoRow* Entry : GameMusicTableRows)
		{
			if (GameMusicGameplayTag == Entry->GameMusicGameplayTag)
			{
				SetSound(Entry->GameMusicSoundCue);
                Play();
				return;
			}
		}

		UE_LOG(LogTemp, Error, TEXT("Unable to find game music of : %s."), *GameMusicGameplayTag.GetTagName().ToString());
	}
}

void UBNGameMusicAudioComponent::RandomlyPlayGameMusic()
{
    if (ensure(GameMusicDataTable))
	{
		TArray<FBNGameMusicTableInfoRow*> GameMusicTableRows;
		GameMusicDataTable->GetAllRows("", GameMusicTableRows);

		const int RandomNumber = FMath::RandRange(0, GameMusicTableRows.Num() - 1);
		SetSound(GameMusicTableRows[RandomNumber]->GameMusicSoundCue);
		Play();
	}
}
