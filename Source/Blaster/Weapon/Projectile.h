// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;
class USoundCue;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class BLASTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;
	
	/** ********** 组件 ********** */
protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;
	
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	/** ********** 伤害 ********** */
protected:
	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ExplodeDamage();

private:
	UPROPERTY(EditAnywhere)
	float DamageInnerRadius = 200.f;

	UPROPERTY(EditAnywhere)
	float DamageOuterRadius = 500.f;
	
	/** ********** 效果 ********** */
protected:
	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere)
	USoundCue* ImpactSound;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* TrailSystem;

	UPROPERTY()
	UNiagaraComponent* TrailSystemComponent;

	void SpawnTrailSystem();
	
private:
	UPROPERTY(EditAnywhere)
	UParticleSystem* Tracer;
	
	UPROPERTY()
	UParticleSystemComponent* TracerComponent;
	
	/** ********** 延迟销毁 ********** */
private:
	FTimerHandle DestroyTimer;

	UPROPERTY(EditAnywhere)
	float DestroyTime = 3.f;

protected:
	void StartDestroyTimer();
	
	void DestroyTimerFinished();
};
