// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "ProjectileRocket.generated.h"

class URocketMovementComponent;
class USoundCue;

UCLASS()
class BLASTER_API AProjectileRocket : public AProjectile
{
	GENERATED_BODY()

public:
	AProjectileRocket();

	virtual void Destroyed() override;
	
protected:
	virtual void BeginPlay() override;
	
	/** ********** 组件 ********** */
private:
	UPROPERTY(VisibleAnywhere)
	URocketMovementComponent* RocketMovementComponent;
	
	/** ********** 伤害 ********** */
protected:
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	/** ********** 效果 ********** */
private:
	UPROPERTY(EditAnywhere)
	USoundCue* ProjectileLoop;

	UPROPERTY(EditAnywhere)
	USoundAttenuation* LoopingSoundAttenuation;
	
	UPROPERTY()
	UAudioComponent* ProjectileLoopComponent;
};
