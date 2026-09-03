// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PR_RaidGameMode.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Engine/TargetPoint.h"

#include "Utils/LogHelper.h"
#include "Actor/PR_Chest.h"
#include "Actor/PR_Dummy.h"
#include "Character/PR_PlayerCharacter.h"
#include "DeveloperSetting/PR_ComboAttackDeveloperSetting.h"


APR_RaidGameMode::APR_RaidGameMode()
{
	CurrentPlayerCount = 1;
	DummyCount = 1;
	CurrentPlayerIndex = 1;
}

void APR_RaidGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	ErrorMessage = TEXT("Raid_Stage_Does_Not_Allow_Join_In_Progress");
	return;
}

void APR_RaidGameMode::SpawnActorLogics()
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
	
	SpawnDummyLogic(World, SpawnPoints);
}

void APR_RaidGameMode::SpawnDummyLogic(UWorld* InWorld, TArray<ATargetPoint*> InSpawnPoints)
{
	const int32 PlayerCount = GameState->PlayerArray.Num();
	
	for (int32 i = 0; i < PlayerCount; ++i)
	{
		FName TargetTag = FName(*FString::Printf(TEXT("SpawnPoint_%d"), i + 1)); 
		
		ATargetPoint** FoundPointPtr = InSpawnPoints.FindByPredicate([TargetTag](const ATargetPoint* Point)
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

			if (InWorld->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
			{
				SpawnLocation.Z = HitResult.ImpactPoint.Z - 145.f;
				SpawnTransform.SetLocation(SpawnLocation);
			}

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
   
			if (APR_Dummy* NewDummy = InWorld->SpawnActor<APR_Dummy>(DummyClass, SpawnTransform, SpawnParams))
			{
				SpawnedDummies.Add(NewDummy);
				
				FString TagName = FString::Printf(TEXT("Player.Index.%d"), i + 1);
				FGameplayTag IndexTag = FGameplayTag::RequestGameplayTag(FName(*TagName));
				NewDummy->SetRequiredPlayerTag(IndexTag);
				SpawnChestLogic(InWorld, NewDummy, i + 1);
			}
		}
	}
}

void APR_RaidGameMode::SpawnChestLogic(UWorld* InWorld, APR_Dummy* InDummy, int32 Index)
{
	if (!InDummy) { return; }
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	if (APR_Chest* NewChest = InWorld->SpawnActor<APR_Chest>(ChestClass,InDummy->GetChestTransform(),SpawnParams))
	{
		FString TagName = FString::Printf(TEXT("Player.Index.%d"), Index);
		FGameplayTag IndexTag = FGameplayTag::RequestGameplayTag(FName(*TagName));
		NewChest->SetRequiredPlayerTag(IndexTag);
		SpawnedChests.Add(NewChest);
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

void APR_RaidGameMode::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	Super::RestartPlayerAtPlayerStart(NewPlayer, StartSpot);
	
	APlayerController* PC = Cast<APlayerController>(NewPlayer);
	if (!PC) return;

	if (APR_PlayerCharacter* TargetChar = Cast<APR_PlayerCharacter>(PC->GetPawn()))
	{
		if (TargetChar->GetPlayerIndexTag().IsValid()) {return;}

		FString TagName = FString::Printf(TEXT("Player.Index.%d"), CurrentPlayerIndex);
		FGameplayTag SlotTag = FGameplayTag::RequestGameplayTag(FName(*TagName));

		TargetChar->SetPlayerIndexTag(SlotTag);
		
		CurrentPlayerIndex++;
	}
}

void APR_RaidGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimerForNextTick(this, &APR_RaidGameMode::SpawnActorLogics);
	}
}

void APR_RaidGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	UPR_ComboAttackDeveloperSetting::PreloadAllWeaponData();
}
