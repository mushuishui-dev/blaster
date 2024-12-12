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

protected:
	void WeaponTraceHit(const FVector& TraceStart, const FVector& HitTarget, FHitResult& OutHit);

	/** ********** 伤害 ********** */
protected:
	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	/** ********** 效果 ********** */
protected:
	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere)
	USoundCue* HitSound;

private:

	UPROPERTY(EditAnywhere)
	UParticleSystem* BeamParticles;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundCue* FireSound;


	/** ********** 散弹 ********** */
protected:
	FVector TraceEndWhithScatter(const FVector& TraceStart, const FVector& HitTarget);

private:
	UPROPERTY(EditAnywhere)
	float DistanceToSphere = 800.f;

	UPROPERTY(EditAnywhere)
	float SphereRadius = 75.f;

	UPROPERTY(EditAnywhere)
	bool bUseScatter = false;
};
