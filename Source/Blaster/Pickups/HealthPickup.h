// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "HealthPickup.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class BLASTER_API AHealthPickup : public APickup
{
	GENERATED_BODY()

public:
	AHealthPickup();

	virtual void Destroyed() override;
	
	/** ********** 组件 ********** */
private:
	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* PickupEffectComponent;

	/** ********** 碰撞检测 ********** */
protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	/** ********** 属性 ********** */
private:
	UPROPERTY(EditAnywhere)
	float HealthAmount = 100.f;

	UPROPERTY(EditAnywhere)
	float HealingTime = 5.f;

	/** ********** 效果 ********** */
private:
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* PickupEffect;
};
