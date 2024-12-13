// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class BLASTER_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	APickup();

	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;
	
protected:
	virtual void BeginPlay() override;
	
	/** ********** 组件 ********** */
private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* OverlapSphere;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PickupMesh;

	/** ********** 碰撞检测 ********** */
protected:
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** ********** 效果 ********** */
private:
	UPROPERTY(EditAnywhere)
	USoundCue* PickupSound;

	/** ********** 旋转 ********** */
private:
	UPROPERTY(EditAnywhere)
	float BaseTurneRate = 45.f;
};
