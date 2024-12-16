// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"

class ABlasterCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

	friend ABlasterCharacter;
	
public:	
	UBuffComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	/** ********** 组合类 ********** */
private:
	ABlasterCharacter* Character;

	/** ********** 治疗增益 ********** */
public:
	void Heal(float HealAmout, float HealingTime);

private:
	bool bHealing = false;

	float HealingRate = 0.f;
	
	float AmountToHeal = 0.f;

	void HealRampUp(float DeltaTime);

	/** ********** 护盾增益增益 ********** */
public:
	void ReplenishShield(float ShieldAmount, float ReplenishTime);

private:
	bool bReplenishShield = false;

	float ShieldReplenishRate = 0.f;

	float ShieldReplenishAmount = 0.f;

	void ShieldRampUp(float DeltaTime);
	
	/** ********** 速度增益 ********** */
public:
	void BuffSpeed(float BuffBaseSpeed, float BuffCrouchSpeed, float BuffTime);

private:
	FTimerHandle SpeedBuffTimer;

	float InitialBaseSpeed;

	float InitialCrouchSpeed;

	void ResetSpeeds();

	void SetInitialSpeeds(float BaseSpeed, float CrouchSpeed);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSpeedBuff(float BaseSpeed, float CrouchSpeed);

	/** ********** 跳跃增益 ********** */
public:
	void SetInitialJumpVeclocity(float Veclocity);

	void BuffJump(float BuffJumpVelocity, float BuffTime);
	
private:
	FTimerHandle JumpBuffTimer;

	float InitialJumpVelocity;
	
	void RestJump();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastJump(float JumpVelocity);
};
