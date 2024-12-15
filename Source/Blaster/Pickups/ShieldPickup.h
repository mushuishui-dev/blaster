// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "ShieldPickup.generated.h"

UCLASS()
class BLASTER_API AShieldPickup : public APickup
{
	GENERATED_BODY()

	/** ********** 碰撞检测 ********** */
protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	/** ********** 属性 ********** */
private:
	UPROPERTY(EditAnywhere)
	float ShieldReplenishAmount = 100.f;

	UPROPERTY(EditAnywhere)
	float ShieldReplenishTime = 5.f;
};
