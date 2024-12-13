// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Casing.generated.h"

class USoundCue;

UCLASS()
class BLASTER_API ACasing : public AActor
{
	GENERATED_BODY()
	
public:	
	ACasing();
	
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	
	/** ********** 组件 ********** */
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CasingMesh;

	/** ********** 碰撞 ********** */
private:
	UPROPERTY(EditAnywhere)
	float ShellEjectionImpluse = 10.f;
	
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** ********** 效果 ********** */
private:
	UPROPERTY(EditAnywhere)
	USoundCue* ShellSound;
};
