// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/PR_GameIntance.h"

#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"

#include "Utils/LogHelper.h"

void UPR_GameIntance::Login()
{
	IOnlineIdentityPtr IdentityPtr = GetIdentityPtr();
	if (IdentityPtr.IsValid())
	{
		if (IdentityPtr->GetLoginStatus(0) == ELoginStatus::LoggedIn)
		{
			LogHelper::LogPrint(TEXT("Already Logged In!"), ELogVerbosity::Warning);
			return;
		}
		
		FOnlineAccountCredentials OnlineAccountCredentials;
		OnlineAccountCredentials.Type = TEXT("accountportal");
		OnlineAccountCredentials.Id = TEXT("");
		OnlineAccountCredentials.Token = TEXT("");
		
		IdentityPtr->Login(0, OnlineAccountCredentials);
	}
	else
	{
		LogHelper::LogPrint(TEXT("Failed to get Identity Interface!"), ELogVerbosity::Error);
	}
}

void UPR_GameIntance::Init()
{
	Super::Init();
	
	OnlineSubsystem = IOnlineSubsystem::Get();
    
	IOnlineIdentityPtr IdentityPtr = GetIdentityPtr();
	if (IdentityPtr.IsValid())
	{
		IdentityPtr->OnLoginCompleteDelegates->AddUObject(this, &UPR_GameIntance::LoginComleted);
	}
}

void UPR_GameIntance::LoginComleted(int NumOfPlayer, bool bSuccessful, const FUniqueNetId& UserID, const FString& Error)
{
	if (bSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Login"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Login failed %s"), *Error);
	}
}

IOnlineIdentityPtr UPR_GameIntance::GetIdentityPtr() const
{
	if (OnlineSubsystem)
	{
		return  OnlineSubsystem->GetIdentityInterface();
	}
	return  nullptr;
}
