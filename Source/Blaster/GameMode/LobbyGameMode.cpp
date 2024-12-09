// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"

ALobbyGameMode::ALobbyGameMode()
{
	bUseSeamlessTravel = true;

}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	if (NumberOfPlayers == 2)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(FString("/Game/Maps/BlasterMap?listen"));
		}
	}
}

void ALobbyGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GEngine) GEngine->AddOnScreenDebugMessage(3, 15.f, FColor::Orange, FString::Printf(TEXT("%0.5f"), GetWorld()->GetTimeSeconds()));

	// SumTime += DeltaSeconds;
	// if (SumTime > 8.f && !bGo)
	// {
	// 	UWorld* World = GetWorld();
	// 	if (World)
	// 	{
	// 		World->ServerTravel(FString("/Game/Maps/BlasterMap?listen"));
	// 		bGo = true;
	// 	}
	// }
	
}
