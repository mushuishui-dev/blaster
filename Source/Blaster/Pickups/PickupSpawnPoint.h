// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpawnPoint.generated.h"

class APickup;

UCLASS()
class BLASTER_API APickupSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupSpawnPoint();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	/** ********** 生成道具 ********** */
private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APickup>> PickupClasses;

	FTimerHandle SpawnPickupTimer;

	UPROPERTY(EditAnywhere)
	float SpawnPickupTimeMin = 1.f;

	UPROPERTY(EditAnywhere)
	float SpawnPickupTimeMax = 5.f;

	UPROPERTY()
	APickup* SpawnedPickup;
	
	void SpawnPickup();

	UFUNCTION()
	void StartSpawnPickup(AActor* DestroyedActor);

	void SpawnPickupTimerFinished();
};
