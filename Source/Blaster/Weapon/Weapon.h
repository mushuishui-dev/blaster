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
	EWS_Dropped UMETA(DisplayName = "Dropped"),
	EWS_MAX UMETA(DisplayName = "DefaultMAX"),
};

class USkeletalMeshComponent;
class USphereComponent;
class UWidgetComponent;
class UAnimationAsset;
class ACasing;
class UTexture2D;

UCLASS()
class BLASTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	 * 准星
	 */
	UPROPERTY(EditAnywhere, Category=Crosshairs)
	UTexture2D* CrosshairsCenter;
	UPROPERTY(EditAnywhere, Category=Crosshairs)
	UTexture2D* CrosshairsLeft;
	UPROPERTY(EditAnywhere, Category=Crosshairs)
	UTexture2D* CrosshairsRight;
	UPROPERTY(EditAnywhere, Category=Crosshairs)
	UTexture2D* CrosshairsTop;
	UPROPERTY(EditAnywhere, Category=Crosshairs)
	UTexture2D* CrosshairsBottom;

	/**
	 * 自动开火
	 */
	UPROPERTY(EditAnywhere, Category=Combat)
	float FireDelay = 0.15f;
	UPROPERTY(EditAnywhere, Category=Combat)
	bool bAutomatic = true;
	
	/**
	 * 武器
	 */
	virtual void Fire(const FVector& HitTarget);
	void Dropped();
	void AddAmmo(int32 AmmoToAdd);

	/**
	 * HUD
	 */
	void ShowPickupWidget(bool bShowWidget);
	void SetHUDAmmo();
	
protected:
	virtual void BeginPlay() override;
	virtual void OnRep_Owner() override;

	/**
	 * 捡枪
	 */
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnSphereEndOVerlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
private:
	/**
	 * 组件
	 */
	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	USphereComponent* AreaSphere;
	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	UWidgetComponent* PickupWidget;
	
	/**
	 * 视角
	 */
	UPROPERTY(EditAnywhere)
	float ZoomedFOV = 30.f;
	UPROPERTY(EditAnywhere)
	float ZoomInterpSpeed = 20.f;

	/**
	 * 武器
	 */
	UPROPERTY(ReplicatedUsing=OnRep_WeaponState, VisibleAnywhere, Category="Weapon Properties")
	EWeaponState WeaponState;
	UFUNCTION()
	void OnRep_WeaponState();
	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType;
	
	/**
	 * 弹药
	 */
	UPROPERTY(EditAnywhere, ReplicatedUsing=OnRep_Ammo)
	int32 Ammo;
	UPROPERTY(EditAnywhere)
	int32 MagCapacity;
	UFUNCTION()
	void OnRep_Ammo();
	void SpendRound();

	/**
	 * Gameplay
	 */
	ABlasterCharacter* BlasterOwnerCharacter;
	ABlasterPlayerController* BlasterOwnerController;
	
	UPROPERTY(EditAnywhere)
	UAnimationAsset* FireAnimation;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACasing> CasingClass;

public:
	/**
	 * Setter or Getter
	 */
	void SetWeaponState(EWeaponState State);
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
	FORCEINLINE float GetZoomedFOV() const { return ZoomedFOV; }
	FORCEINLINE float GetZoomInterpSpeed() const { return ZoomInterpSpeed; }
	bool IsEmpty();
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	FORCEINLINE int32 GetMagCapacity() const { return MagCapacity; }
	FORCEINLINE int32 GetAmmo() const { return Ammo; }
	
};
