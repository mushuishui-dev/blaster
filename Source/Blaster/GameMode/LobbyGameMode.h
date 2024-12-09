// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ALobbyGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/**
	 * 测试
	 */
	virtual void Tick(float DeltaSeconds) override;
	
private:
	/**
	 * 测试
	 */
	float SumTime = 0.f;
	float bGo = false;
};
