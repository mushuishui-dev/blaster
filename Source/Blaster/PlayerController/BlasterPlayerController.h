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

protected:
	virtual void BeginPlay() override;

	void PollInit();

	/** ********** 组合类 ********** */
private:
	UPROPERTY()
	ABlasterHUD* BlasterHUD;
	
	UPROPERTY()
	ABlasterGameMode* BlasterGameMode;

	UPROPERTY()
	UCharacterOverlay* CharacterOverlay;

	/** ********** HUD ********** */
public:
	void SetHUDHealth(float Health, float MaxHealth);
	
	void SetHUDScore(float Score);
	
	void SetHUDDefeats(int32 Defeats);
	
	void SetHUDWeaponAmmo(int32 Ammo);
	
	void SetHUDCarriedAmmo(int32 Ammo);
	
	void SetHUDMatchCountdown(float Countdown);
	
	void SetHUDAnnouncementCountdown(float Countdown);

protected:
	/** 更新热身和冷却倒计时 */
	void SetHUDTime();

private:
	float HUDHealth = 0.f;
	
	float HUDMaxHealth = 0.f;
	
	float HUDScore = 0.f;
	
	int32 HUDDefeats = 0;

	int32 CountdownTime = 0;
	
	float WarmupTime = 0.f;
	
	float MatchTime = 0.f;
	
	float CooldownTime = 0.f;
	
	float LevelStartingTime = 0.f;

	/** ********** 时间同步 ********** */
protected:
	/** 服务器与客户端的世界时间差 */
	float ServerClientDelta = 0.f;

	UPROPERTY(EditAnywhere)
	float TimeSyncFrequency = 5.f;

	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);
	
	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);
	
	float GetServerTime();

	void CheckTimeSync(float DeltaTime);
	
private:
	float TimeSyncRunningTime = 0.f;

	/** ********** 游戏状态 ********** */
public:
	void OnMatchStateSet(FName State);
	
private:
	UPROPERTY(ReplicatedUsing=OnRep_MatchState)
	FName MatchState;
	
	UFUNCTION()
	void OnRep_MatchState();

	UFUNCTION(Server, Reliable)
	void ServerCheckMatchState();
	
	UFUNCTION(Client, Reliable)
	void ClientJoinMidGame(FName StateOfMatch, float Warmup, float Match, float Cooldown, float StartingTime);
	
	void HandleMatchHasStarted();
	
	void HandleCooldown();
};
