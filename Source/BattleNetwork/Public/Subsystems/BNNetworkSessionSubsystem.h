// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "BNNetworkSessionSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNNetworkSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	
	/* Delegate called when session created */
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	/* Delegate called when session started */
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	/** Handles to registered delegates for creating/starting a session */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	/** Delegate for searching for sessions */
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	/** Delegate for joining a session */
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	/** Handle to registered delegate for joining a session */
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	/** Handle to registered delegate for searching a session */
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	/** Handle to registered delegate for destroying a session */
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
public:

	UBNNetworkSessionSubsystem();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void StartOnlineGame();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void FindOnlineGames();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void JoinOnlineGame();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void DestroySessionAndLeaveGame();

protected:

	bool HostSession(const FUniqueNetId& UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	void FindSessions(const FUniqueNetId& UserId, bool bIsLAN, bool bIsPresence);

	bool JoinSession(const FUniqueNetId& UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);
	
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);
	
	void OnFindSessionsComplete(bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
};
