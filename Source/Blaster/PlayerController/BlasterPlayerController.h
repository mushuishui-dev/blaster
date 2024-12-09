// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

class ABlasterGameMode;
class UCharacterOverlay;
class ABlasterHUD;

UCLASS()
class BLASTER_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void ReceivedPlayer() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	 * 设置HUD
	 */
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDScore(float Score);
	void SetHUDDefeats(int32 Defeats);
	void SetHUDWeaponAmmo(int32 Ammo);
	void SetHUDCarriedAmmo(int32 Ammo);
	void SetHUDMatchCountdown(float Countdown);
	void SetHUDAnnouncementCountdown(float Countdown);

	/**
	 * 游戏状态
	 */
	void OnMatchStateSet(FName State);
	void HandleMatchHasStarted();
	void HandleCooldown();
	
protected:
	virtual void BeginPlay() override;

	/**
	 * 时间同步
	 */
	UPROPERTY(EditAnywhere)
	float TimeSyncFrequency = 5.f;
	float ServerClientDelta = 0.f;
	float TimeSyncRunningTime = 0.f;
	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);
	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);
	void CheckTimeSync(float DeltaTime);
	virtual float GetServerTime();

	/**
	 * 比赛状态
	 */
	UFUNCTION(Server, Reliable)
	void ServerCheckMatchState();
	UFUNCTION(Client, Reliable)
	void ClientJoinMidGame(FName StateOfMatch, float Warmup, float Match, float Cooldown, float StartingTime);
	
	void PollInit();
	
	void SetHUDTime();

private:
	/**
	 * 计时
	 */
	float WarmupTime;
	float MatchTime;
	float CooldownTime;
	float LevelStartingTime;
	int32 CountdownTime = 0;
	
	/**
	 * 比赛状态
	 */
	UPROPERTY(ReplicatedUsing=OnRep_MatchState)
	FName MatchState;
	UFUNCTION()
	void OnRep_MatchState();

	/**
	 * 头显初始化
	 */
	UPROPERTY()
	UCharacterOverlay* CharacterOverlay;
	bool bInitializeCharacterOverlay = false;
	float HUDHealth;
	float HUDMaxHealth;
	float HUDScore;
	int32 HUDDefeats;

	/**
	 * Gameplay
	 */
	UPROPERTY()
	ABlasterHUD* BlasterHUD;
	UPROPERTY()
	ABlasterGameMode* BlasterGameMode;

};
