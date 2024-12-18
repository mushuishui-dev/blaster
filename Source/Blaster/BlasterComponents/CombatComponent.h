// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blaster/BlasterTypes/CombatState.h"
#include "Blaster/HUD/BlasterHUD.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class AProjectile;
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

protected:
	virtual void BeginPlay() override;
	
	/** ********** 组合类 ********** */
private:
	UPROPERTY()
	ABlasterCharacter* Character;
	
	UPROPERTY()
	ABlasterPlayerController* Controller;
	
	UPROPERTY()
	ABlasterHUD* HUD;

	/** ********** 装备武器 ********** */
private:
	UPROPERTY(ReplicatedUsing=OnRep_EquippedWeapon)
	AWeapon* EquippedWeapon;

	UPROPERTY(ReplicatedUsing=OnRep_SecondaryWeapon)
	AWeapon* SecondaryWeapon;
	
	void EquipWeapon(AWeapon* WeaponToEquip);

	void SwapWeapons();
	
	void EquipPrimaryWeapon(AWeapon* WeaponToEquip);

	void EquipSecondaryWeapon(AWeapon* WeaponToEquip);
	
	UFUNCTION()
	void OnRep_EquippedWeapon();

	UFUNCTION()
	void OnRep_SecondaryWeapon();

	void DropEquippedWeapon();

	void AttachActorToRightHand(AActor* ActorToAttach);

	void AttachActorToBackpack(AActor* ActorToAttach);

	void PlayEquippedSound(AWeapon* WeaponToEquip);

	bool ShouldSwapWeapons();
	
	/** ********** 瞄准 ********** */
public:
	void SetAiming(bool bIsAiming);
	
private:
	UPROPERTY(ReplicatedUsing=OnRep_Aiming)
	bool bAiming = false;

	bool bAimButtonPressed = false;
	
	UFUNCTION()
	void OnRep_Aiming();
	
	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bIsAiming);
	
	/** ********** 开火 ********** */
public:
	void FireButtonPressed(bool bPressed);

private:
	bool bFireButtonPressed;
	
	void Fire();

	void LocalFire(const FVector_NetQuantize& TraceHitTarget);

	void ShotgunLocalFire(const TArray<FVector_NetQuantize>& TraceHitTargets);
	
	void FireProjectileWeapon();

	void FireHitScanWeapon();

	void FireShotgun();
	
	UFUNCTION(Server, Reliable)
	void ServerFire(const FVector_NetQuantize& TraceHitTarget); // FVector_NetQuantize 网络优化
	
	UFUNCTION(NetMulticast, Reliable)
	void MultcastFire(const FVector_NetQuantize& TraceHitTarget);

	UFUNCTION(Server, Reliable)
	void ServerShotgunFire(const TArray<FVector_NetQuantize>& TraceHitTargets);
	
	UFUNCTION(NetMulticast, Reliable)
	void MultcastShotgunFire(const TArray<FVector_NetQuantize>& TraceHitTargets);

	bool CanFire();

	/** ********** 移动速度 ********** */
private:
	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed = 600.f;
	
	UPROPERTY(EditAnywhere)
	float AimWalkSpeed = 400.f;

	/** ********** 准星 ********** */
private:
	FVector HitTarget;
	
	FHUDPackage HUDPackage;
	
	float CrosshairVelocityFactor;
	
	float CrosshairInAirFactor;
	
	float CrosshairAimFactor;
	
	float CrosshairShootingFactor;
	
	void TraceUnderCrosshairs(FHitResult& TraceHitResult);
	
	void SetHUDCrosshairs(float DeltaTime);

	/** ********** 视角缩放 ********** */
private:
	void InterpFOV(float DeltaTime);
	
	float DefaultFOV;
	
	float CurrentFOV;

	/** 从瞄准视角到正常视角的速度 */
	UPROPERTY(EditAnywhere)
	float ZoomInterpSpeed = 20.f;

	/** ********** 自动开火 ********** */
private:
	FTimerHandle FireTimer;
	
	bool bCanFire = true;
	
	void StartFireTimer();
	
	void FireTimerFinished();
	
	/** ********** 弹药 ********** */
public:
	UFUNCTION(BlueprintCallable)
	void FinishReloading();
	
private:
	/** 当前类型武器的备弹 */
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_CarriedAmmo)
	int32 CarriedAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 MaxCarriedAmmo = 500;
	
	TMap<EWeaponType, int32> CarriedAmmoMap;
	
	UPROPERTY(EditAnywhere)
	int32 StartingARAmmo = 30;

	UPROPERTY(EditAnywhere)
	int32 StartingRocketAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingPistolAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingSMGAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingShotgunAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingSniperAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingGrenadeAmmo = 0;

	bool bLocallyReloading = false;
	
	void Reload();
	
	UFUNCTION(Server, Reliable)
	void ServerReload();
	
	void HandleReload();
	
	UFUNCTION()
	void OnRep_CarriedAmmo();
	
	void InitializeCarriedAmmo();
	
	int32 AmountToReload();

	void UpdateAmmoValues();

	void UpdateCarriedAmmo();

	void ReloadEmptyWeapon();
	
	/** ********** 战斗状态 ********** */
private:
	UPROPERTY(ReplicatedUsing=OnRep_CombatState)
	ECombatState CombatState = ECombatState::ECS_Unoccupied;
	
	UFUNCTION()
	void OnRep_CombatState();

	/** ********** 霰弹枪换弹 ********** */
public:
	UFUNCTION(BlueprintCallable)
	void ShotgunShellReload();

	void JumpToShotgunEnd();
	
private:
	void UpdateShotgunAmmoValues();

	/** ********** 手榴弹 ********** */
public:
	UFUNCTION(BlueprintCallable)
	void ThrowGrenadeFinished();

	UFUNCTION(BlueprintCallable)
	void LaunchGrenade();
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> GrenadeClass;

	UPROPERTY(ReplicatedUsing=OnRep_Grenades)
	int32 Grenades = 4;

	UPROPERTY(EditAnywhere)
	int32 MaxGrenades = 4;

	void ThrowGrenade();

	UFUNCTION(Server, Reliable)
	void ServerThrowGrenade();
	
	void AttachActorToLeftHand(AActor* ActorToAttach);

	void ShowAttachedGrenade(bool bShowGrenade);

	UFUNCTION(Server, Reliable)
	void ServerLaunchGrenade(const FVector_NetQuantize& Target);

	UFUNCTION()
	void OnRep_Grenades();

	void UpdateHUDGrenades();

public:
	FORCEINLINE int32 GetGrenades() const { return Grenades; }

	/** ********** 拾取弹药 ********** */
public:
	void PickupAmmo(EWeaponType WeaponType, int32 AmmoAmount);
};