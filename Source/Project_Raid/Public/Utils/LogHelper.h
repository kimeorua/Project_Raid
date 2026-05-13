#pragma once
#include "Engine.h"

namespace LogHelper
{
	static void LogPrint(const FString& Msg, ELogVerbosity::Type Verbosity = ELogVerbosity::Warning, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			FColor FinalColor = Color;
			if (Verbosity == ELogVerbosity::Error) FinalColor = FColor::Red;
            
			GEngine->AddOnScreenDebugMessage(InKey, 7.0f, FinalColor, Msg);
		}
		
		switch (Verbosity)
		{
		case ELogVerbosity::Error:
			UE_LOG(LogTemp, Error, TEXT("%s"), *Msg);
			break;
		case ELogVerbosity::Display:
			UE_LOG(LogTemp, Display, TEXT("%s"), *Msg);
			break;
		case ELogVerbosity::Warning:
		default:
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
			break;
		}
	}

	static void LogPrint(const FString& FloatTitle, float FloatValueToPrint, ELogVerbosity::Type Verbosity = ELogVerbosity::Warning, const FColor& Color = FColor::MakeRandomColor(),  int32 InKey = -1)
	{
		if (GEngine)
		{
			const FString FinalMsg = FloatTitle + TEXT(":  ") + FString::SanitizeFloat(FloatValueToPrint);

			LogPrint(FinalMsg, Verbosity, Color, InKey);
		}
	}
}