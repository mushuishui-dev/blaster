// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

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
	void SetHUDMatchCountdown(float CoutdownTime);

	virtual float GetServerTime();

	/**
	 * 游戏状态
	 */
	void OnMatchStateSet(FName State);
	void HandleMatchHasStarted();
	
protected:
	virtual void BeginPlay() override;

	/**
	 * 计时
	 */
	float ServerClientDelta = 0.f;
	UPROPERTY(EditAnywhere)
	float TimeSyncFrequency = 5.f;
	float TimeSyncRunningTime = 0.f;
	void SetHUDTime();
	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);
	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);
	void CheckTimeSync(float DeltaTime);

	void PollInit();
	
private:
	/**
	 * 计时
	 */
	float MatchTime = 120.f;
	uint32 CountdownTime = 0;
	
	UPROPERTY()
	ABlasterHUD* BlasterHUD;

	/**
	 * 比赛状态
	 */
	UPROPERTY(ReplicatedUsing=OnRep_MatchState)
	FName MatchState;
	UFUNCTION()
	void OnRep_MatchState();

	/**
	 * 头显
	 */
	UPROPERTY()
	UCharacterOverlay* CharacterOverlay;
	bool bInitializeCharacterOverlay = false;
	float HUDHealth;
	float HUDMaxHealth;
	float HUDScore;
	int32 HUDDefeats;
	
};
