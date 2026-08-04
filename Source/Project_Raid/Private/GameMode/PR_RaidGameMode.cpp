// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PR_RaidGameMode.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"

#include "Actor/PR_Dummy.h"
#include "Engine/TargetPoint.h"
#include "Utils/LogHelper.h"

APR_RaidGameMode::APR_RaidGameMode()
{
	CurrentPlayerCount = 1;
	DummyCount = 1;
}

void APR_RaidGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	ErrorMessage = TEXT("Raid_Stage_Does_Not_Allow_Join_In_Progress");
	return;
}

void APR_RaidGameMode::SpawnDummiesForConnectedPlayers()
{
	if (!DummyClass) { return; }

	UWorld* World = GetWorld();
	if (!World) { return; }
	
	if (!GameState || GameState->PlayerArray.Num() == 0) { return; }
	
	TArray<ATargetPoint*> SpawnPoints;
	for (TActorIterator<ATargetPoint> It(World); It; ++It)
	{
		if (ATargetPoint* Point = *It)
		{
			SpawnPoints.Add(Point);
		}
	}
	
	const int32 PlayerCount = GameState->PlayerArray.Num();
	
	for (int32 i = 0; i < PlayerCount; ++i)
	{
		FName TargetTag = FName(*FString::Printf(TEXT("SpawnPoint_%d"), i + 1)); 
		
		ATargetPoint** FoundPointPtr = SpawnPoints.FindByPredicate([TargetTag](const ATargetPoint* Point)
		{
		   return Point && Point->ActorHasTag(TargetTag);
		});
		
		if (FoundPointPtr && *FoundPointPtr)
		{
			ATargetPoint* TargetSpawnPoint = *FoundPointPtr;
			FTransform SpawnTransform = TargetSpawnPoint->GetActorTransform();
			FVector SpawnLocation = SpawnTransform.GetLocation();
			
			FHitResult HitResult;
			FVector TraceStart = SpawnLocation;
			FVector TraceEnd = SpawnLocation - FVector(0.0f, 0.0f, 2000.0f);

			FCollisionQueryParams TraceParams;
			TraceParams.AddIgnoredActor(TargetSpawnPoint);

			if (World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
			{
				SpawnLocation.Z = HitResult.ImpactPoint.Z - 145.f;
				SpawnTransform.SetLocation(SpawnLocation);
			}
			else
			{
				DrawDebugLine(World, TraceStart, TraceEnd, FColor::Red, false, 5.0f, 0, 2.0f);
			}

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
   
			if (APR_Dummy* NewDummy = World->SpawnActor<APR_Dummy>(DummyClass, SpawnTransform, SpawnParams))
			{
				SpawnedDummies.Add(NewDummy);
			}
		}
	}
}

AActor* APR_RaidGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	FName TargetTag = FName(*FString::Printf(TEXT("Spawn_%d"), CurrentPlayerCount));
    
	APlayerStart* FoundStart = nullptr;
	
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* PlayerStart = *It;
		if (PlayerStart && PlayerStart->PlayerStartTag == TargetTag)
		{
			FoundStart = PlayerStart;
			break;
		}
	}

	CurrentPlayerCount++;

	return FoundStart ? FoundStart : Super::ChoosePlayerStart_Implementation(Player);
}

void APR_RaidGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimerForNextTick(this, &APR_RaidGameMode::SpawnDummiesForConnectedPlayers);
	}
}
