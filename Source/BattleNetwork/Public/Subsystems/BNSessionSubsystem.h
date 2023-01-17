// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "BNSessionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBNOnCreateSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBNOnUpdateSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBNOnStartSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBNOnEndSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBNOnDestroySessionComplete, bool, Successful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBNOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool Successful);
DECLARE_MULTICAST_DELEGATE_OneParam(FBNOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);

UCLASS()
class BATTLENETWORK_API UBNSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;
	
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;

	FOnUpdateSessionCompleteDelegate UpdateSessionCompleteDelegate;
	FDelegateHandle UpdateSessionCompleteDelegateHandle;

	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;

	FOnEndSessionCompleteDelegate EndSessionCompleteDelegate;
	FDelegateHandle EndSessionCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;

	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	
public:

	UBNSessionSubsystem();

	void CreateSession(int32 NumberPublicConnections, bool IsLANMatch, FName MapName);

	void UpdateSession();

	void StartSession();

	void EndSession();

	void DestroySession();

	void FindSessions(int32 MaxSearchResults, bool IsLANQuery);

	void JoinGameSession(const FOnlineSessionSearchResult& SessionResult);

	FBNOnCreateSessionComplete OnCreateSessionCompleteEvent;

	FBNOnUpdateSessionComplete OnUpdateSessionCompleteEvent;

	FBNOnStartSessionComplete OnStartSessionCompleteEvent;

	FBNOnEndSessionComplete OnEndSessionCompleteEvent;

	FBNOnDestroySessionComplete OnDestroySessionCompleteEvent;

	FBNOnFindSessionsComplete OnFindSessionsCompleteEvent;

	FBNOnJoinSessionComplete OnJoinGameSessionCompleteEvent;
	
protected:

	void OnCreateSessionCompleted(FName SessionName, bool Successful);

	void OnUpdateSessionCompleted(FName SessionName, bool Successful);

	void OnStartSessionCompleted(FName SessionName, bool Successful);
	
	void OnEndSessionCompleted(FName SessionName, bool Successful);

	void OnDestroySessionCompleted(FName SessionName, bool Successful);

	void OnFindSessionsCompleted(bool Successful);

	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
	bool TryTravelToCurrentSession();
};
