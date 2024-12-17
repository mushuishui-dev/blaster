// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitScanWeapon.h"
#include "Shotgun.generated.h"

UCLASS()
class BLASTER_API AShotgun : public AHitScanWeapon
{
	GENERATED_BODY()

	/** ********** 开火 ********** */
public:
	void FireShotgun(const TArray<FVector_NetQuantize>& HitTargets);
	
	/** ********** 散弹 ********** */
public:
	void ShotgunTraceEndWithScatter(const FVector& HitTarget, TArray<FVector_NetQuantize>& HitTargets);

private:
	UPROPERTY(EditAnywhere)
	int32 NumberOfPellets = 12;
};
