// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "HitScanWeapon.generated.h"

class USoundCue;

UCLASS()
class BLASTER_API AHitScanWeapon : public AWeapon
{
	GENERATED_BODY()

	/** ********** 开火 ********** */
public:
	virtual void Fire(const FVector& HitTarget) override;

	/** ********** 伤害 ********** */
private:
	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	/** ********** 效果 ********** */
private:
	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere)
	UParticleSystem* BeamParticles;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundCue* FireSound;

	UPROPERTY(EditAnywhere)
	USoundCue* HitSound;
};
