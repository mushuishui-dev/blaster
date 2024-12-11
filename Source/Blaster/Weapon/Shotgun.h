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
	virtual void Fire(const FVector& HitTarget) override;

	/** ********** 散弹 ********** */
private:
	UPROPERTY(EditAnywhere)
	int32 NumberOfPellets = 12;
};
