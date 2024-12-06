// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blaster/HUD/BlasterHUD.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

#define TRACE_LENGTH 80000.f;

enum class EWeaponType : uint8;
class ABlasterHUD;
class ABlasterPlayerController;
class ABlasterCharacter;
class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()
	
	friend ABlasterCharacter;
	
public:	
	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	void EquipWeapon(AWeapon* WeaponToEquip);

protected:
	virtual void BeginPlay() override;

	/**
	 * 瞄准
	 */
	void SetAiming(bool bIsAiming);
	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bIsAiming);

	/**
	 * 开火
	 */
	void FireButtonPressed(bool bPressed);
	// FVector_NetQuantize，网络优化
	void Fire();
	UFUNCTION(Server, Reliable)
	void ServerFire(const FVector_NetQuantize& TraceHitTarget);
	UFUNCTION(NetMulticast, Reliable)
	void MultcastFire(const FVector_NetQuantize& TraceHitTarget);

	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

	void SetHUDCrosshairs(float DeltaTime);

	UFUNCTION()
	void OnRep_EquippedWeapon();

private:
	/**
	 * Gameplay
	 */
	UPROPERTY()
	ABlasterCharacter* Character;
	UPROPERTY()
	ABlasterPlayerController* Controller;
	UPROPERTY()
	ABlasterHUD* HUD;

	/**
	 * 速度
	 */
	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed;
	UPROPERTY(EditAnywhere)
	float AimWalkSpeed;

	/**
	 * 准星
	 */
	FHUDPackage HUDPackage;
	float CrosshairVelocityFactor;
	float CrosshairInAirFactor;
	float CrosshairAimFactor;
	float CrosshairShootingFactor;
	
	/**
	 * 视角
	 */
	void InterpFOV(float DeltaTime);
	float DefaultFOV;
	float CurrentFOV;
	UPROPERTY(EditAnywhere, Category=Combat)
	float ZoomedFOV = 30.f;
	UPROPERTY(EditAnywhere, Category=Combat)
	float ZoomInterpSpeed = 20.f;

	/**
	 * 自动开火
	 */
	FTimerHandle FireTimer;
	bool bCanFire = true;
	void StartFireTimer();
	void FireTimerFinished();

	/**
	 * 备弹
	 */
	UPROPERTY(EditAnywhere, ReplicatedUsing=OnRep_CarriedAmmo)
	int32 CarriedAmmo;
	TMap<EWeaponType, int32> CarriedAmmoMap;
	UFUNCTION()
	void OnRep_CarriedAmmo();
	
	UPROPERTY(ReplicatedUsing=OnRep_EquippedWeapon)
	AWeapon* EquippedWeapon;

	UPROPERTY(Replicated)
	bool bAiming;

	bool bFireButtonPressed;

	FVector HitTarget;

	bool CanFire();

};
