// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

enum class EWeaponType : uint8;
class ABlasterPlayerController;
class ABlasterCharacter;

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Initial UMETA(DisplayName = "Initial State"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_EquippedSecondary UMETA(DisplayName = "Equipped Secondary"),
	EWS_Dropped UMETA(DisplayName = "Dropped"),
	
	EWS_MAX UMETA(DisplayName = "DefaultMAX")
};

class USkeletalMeshComponent;
class USphereComponent;
class UWidgetComponent;
class UAnimationAsset;
class ACasing;
class UTexture2D;
class USoundCue;

UCLASS()
class BLASTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;
	
	virtual void OnRep_Owner() override;

	/** ********** 组合类 ********** */
private:
	ABlasterCharacter* BlasterOwnerCharacter;
	
	ABlasterPlayerController* BlasterOwnerController;
	
	/** ********** 组件 ********** */
private:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* AreaSphere;
	
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* PickupWidget;

public:
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }
	
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
	
	/** ********** 准星 ********** */
public:
	UPROPERTY(EditAnywhere)
	UTexture2D* CrosshairsCenter;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* CrosshairsLeft;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* CrosshairsRight;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* CrosshairsTop;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* CrosshairsBottom;

	/** ********** 自动开火 ********** */
private:
	UPROPERTY(EditAnywhere)
	float FireDelay = 0.15f;

	UPROPERTY(EditAnywhere)
	bool bAutomatic = true;
	
public:
	FORCEINLINE float GetFireDelay() const { return FireDelay; }
	
	FORCEINLINE bool IsAutomatic() const { return bAutomatic; }

	/** ********** 开火 丢弃 ********** */
public:
	virtual void Fire(const FVector& HitTarget);

	void Dropped();

	/** ********** HUD ********** */
public:
	void ShowPickupWidget(bool bShowWidget);

	void SetHUDAmmo();
	
	/** ********** 碰撞检测 ********** */
private:
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOVerlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** ********** 视角缩放 ********** */
private:
	/** 瞄准视角大小 */
	UPROPERTY(EditAnywhere)
	float ZoomedFOV = 30.f;

	/** 从正常视角到瞄准视角的速度 */
	UPROPERTY(EditAnywhere)
	float ZoomInterpSpeed = 20.f;
	
public:
	FORCEINLINE float GetZoomedFOV() const { return ZoomedFOV; }
	
	FORCEINLINE float GetZoomInterpSpeed() const { return ZoomInterpSpeed; }

	/** ********** 武器状态 ********** */
public:
	void SetWeaponState(EWeaponState State);
	
private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_WeaponState)
	EWeaponState WeaponState;
	
	UFUNCTION()
	void OnRep_WeaponState();

	void OnWeaponStateSet();

	void OnEquipped();
	
	void OnDropped();
	
	void OnEquippedSecondary();
	
	/** ********** 武器类型 ********** */
private:
	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType;
	
public:
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	
	/** ********** 弹药 ********** */
public:
	bool IsEmpty();

	bool IsFull();
	
	void AddAmmo(int32 AmmoToAdd);
	
private:
	/** 当前弹容量 */
	UPROPERTY(EditAnywhere, ReplicatedUsing=OnRep_Ammo)
	int32 Ammo;

	/** 最大弹容量 */
	UPROPERTY(EditAnywhere)
	int32 MagCapacity;
	
	UFUNCTION()
	void OnRep_Ammo();
	
	void SpendRound();
	
public:
	FORCEINLINE int32 GetMagCapacity() const { return MagCapacity; }
	
	FORCEINLINE int32 GetAmmo() const { return Ammo; }

	/** ********** 效果 ********** */
public:
	UPROPERTY(EditAnywhere)
	USoundCue* EquipSound;

	void EnableCustomDepth(bool bEnable);
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACasing> CasingClass;

	UPROPERTY(EditAnywhere)
	UAnimationAsset* FireAnimation;

	/** ********** 默认武器 ********** */
public:
	bool bDestroyWeapon = false;
};
