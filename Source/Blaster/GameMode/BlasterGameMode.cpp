// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterGameMode.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"
#include "Blaster/PlayerState/BlasterPlayerState.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

namespace MatchState
{
	const FName Cooldown = FName("Cooldown");
}

ABlasterGameMode::ABlasterGameMode()
{
	bDelayedStart = true;
	
}

void ABlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds();
	
	/**
	 * 测试
	 */
	if (GEngine) GEngine->AddOnScreenDebugMessage(2, 15.f, FColor::Red, FString::Printf(TEXT("%0.5f"), LevelStartingTime));

}

void ABlasterGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MatchState == MatchState::WaitingToStart)
	{
		CoutdownTime = WarmupTime - (GetWorld()->GetTimeSeconds() - LevelStartingTime);
		if (CoutdownTime <= 0.f)
		{
			StartMatch();
		}
	}
	else if (MatchState == MatchState::InProgress)
	{
		CoutdownTime = MatchTime + WarmupTime - (GetWorld()->GetTimeSeconds() - LevelStartingTime);
		if (CoutdownTime <= 0.f)
		{
			SetMatchState(MatchState::Cooldown);
		}
	}
	
}

void ABlasterGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		ABlasterPlayerController* BlasterPlayer = Cast<ABlasterPlayerController>(*It);
		if (BlasterPlayer)
		{
			BlasterPlayer->OnMatchStateSet(MatchState);
		}
	}
	
}

void ABlasterGameMode::PlayerEliminated(ABlasterCharacter* ElimmedCharacter, ABlasterPlayerController* VictimController,
                                        ABlasterPlayerController* AttackerController)
{
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Elim();
	}

	// 计分
	ABlasterPlayerState* AttackerPlayerState = AttackerController ? AttackerController->GetPlayerState<ABlasterPlayerState>() : nullptr;
	ABlasterPlayerState* VictimPlayerState = VictimController ? VictimController->GetPlayerState<ABlasterPlayerState>() : nullptr;
	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState)
	{
		AttackerPlayerState->AddToScore(1.f);
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->AddToDefeats(1);
	}

}

void ABlasterGameMode::RequestRespawn(ACharacter* ElimeedCharacter, AController* ElimeedController)
{
	if (ElimeedCharacter)
	{
		ElimeedCharacter->Reset();
		ElimeedCharacter->Destroy();
	}
	if (ElimeedController)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(ElimeedController, PlayerStarts[Selection]);
	}
	
}