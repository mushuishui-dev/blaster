// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "Blaster/Interfaces/InteractWithCrosshairsInterface.h"
#include "Blaster/Weapon/Weapon.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "BlasterCharacter.generated.h"

enum class ECombatState : uint8;
class UBuffComponent;
class ABlasterPlayerState;
class UTimelineComponent;
class ABlasterPlayerController;
class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
class AWeapon;
class UCombatComponent;
class UAnimMontage;
class UBoxComponent;
class ULagCompensationComponent;

UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter, public IInteractWithCrosshairsInterface
{
	GENERATED_BODY()

public:
	ABlasterCharacter();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PostInitializeComponents() override;
	
	virtual void Destroyed() override;

	virtual void OnRep_ReplicatedMovement() override;

	virtual void Jump() override;

private:
	/** 轮询初始化 处理在BeginPlay中无法初始化的情况 */
	void PollInit();

	/** ********** 组合类 ********** */
private:
	UPROPERTY()
	ABlasterPlayerController* BlasterPlayerController;
	
	UPROPERTY()
	ABlasterPlayerState* BlasterPlayerState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCombatComponent* Combat;

	UPROPERTY(VisibleAnywhere)
	UBuffComponent* Buff;
	
public:
	FORCEINLINE UCombatComponent* GetCombat() const { return Combat; }

	FORCEINLINE UBuffComponent* GetBuff() const { return Buff; }
	
	AWeapon* GetEquippedWeapon();
	
	bool IsWeaponEquipped();
	
	bool IsAiming();
	
	ECombatState GetCombatState() const;

	FVector GetHitTarget() const;

	bool IsLocallyReloading() const;
	
	/** ********** 组件 ********** */
private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UWidgetComponent* OverheadWidget;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AttachedGrenade;

	UPROPERTY(VisibleAnywhere)
	ULagCompensationComponent* LagCompensation;
	
public:
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE UStaticMeshComponent* GetAttachedGrenade() const { return AttachedGrenade; }

	FORCEINLINE ULagCompensationComponent* GetLagCompensation() const { return LagCompensation; }
	
	/** ********** 输入 ********** */
private:
	UPROPERTY(Replicated)
	bool bDisableGameplay = false;

	void MoveForward(float Value);
	
	void MoveRight(float Value);
	
	void Turn(float Value);
	
	void LookUp(float Value);
	
	void EquipButtonPressed();

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();
	
	void CrouchButtonPressed();
	
	void AimButtonPressed();
	
	void AimButtonReleased();
	
	void FireButtonPressed();
	
	void FireButtonReleased();
	
	void ReloadButtonPressed();

	void GrenadeButtonPressed();
	
public:
	FORCEINLINE void SetDisableGameplay(bool Value) { bDisableGameplay = Value; }
	FORCEINLINE bool GetDisableGameplay() const { return bDisableGameplay; }

	/** ********** 瞄准偏移 ********** */
private:
	float AO_Yaw = 0.f;
	
	float AO_Pitch = 0.f;
	
	FRotator StartingAimRotation;
	
	float CalculateSpeed();

	void CalculateAO_Pitch();
	
	void AimOffset(float DeltaTime);
	
public:
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }
	
	/** ********** 转身 ********** */
private:
	ETurningInPlace TurningInPlace;
	
	float InterpAO_Yaw = 0.f;
	
	bool bRotateRootBone = true;
	
	/** 模拟代理的转身阈值 */
	float TurnThreshold = 0.5f;
	
	FRotator ProxyRotationLastFrame;
	
	FRotator ProxyRotation;
	
	float ProxyYaw = 0.f;

	float TimeSinceLastMovementReplication = 0.f;
	
	void TurnInPlace(float DeltaTime);
	
	void RotateInPlace(float DeltaTime);
	
	void SimProxiesTurn();

public:
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }
	
	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }

	/** ********** 装备武器 ********** */
public:
	void SetOverlappingWeapon(AWeapon* Weapon);

private:
	UPROPERTY(ReplicatedUsing=OnRep_OverlappingWeapon)
	AWeapon* OverlappingWeapon;
	
	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	/** ********** 动画 ********** */
public:
	void PlayFireMotage(bool bAiming);
	
	void PlayHitReactMotage();
	
	void PlayElimMotage();
	
	void PlayReloadMotage();

	void PlayThrowGrenadeMotag();
	
private:
	UPROPERTY(EditAnywhere)
	UAnimMontage* FireWeaponMotage;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* HitReactMotage;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* ElimMotage;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* ReloadMotage;

	UPROPERTY(EditAnywhere)
	UAnimMontage* ThrowGrenadeMotage;
	
public:
	FORCEINLINE UAnimMontage* GetReloadMotage() const { return ReloadMotage; }
	
	/** ********** 摄像机隐藏 ********** */
private:
	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;
	
	void HideCameraIfCharacterClose();

	/** ********** 生命 ********** */
public:
	void UpdateHUDHealth();
	
private:
	UPROPERTY(ReplicatedUsing=OnRep_Health, VisibleAnywhere)
	float Health = 100.f;
	
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	
	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnRep_Health(float LastHealth);

public:
	FORCEINLINE float GetHealth() const { return Health; }
	
	FORCEINLINE void SetHealth(float Amount) { Health = Amount; }
	
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	/** ********** 护盾 ********** */
public:
	void UpdateHUDShield();

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Shield)
	float Shield = 0.f;

	UPROPERTY(EditAnywhere)
	float MaxShield = 100.f;

	UFUNCTION()
	void OnRep_Shield(float LastShield);

public:
	FORCEINLINE float GetShield() const { return Shield; }
	
	FORCEINLINE void SetShield(float Amount) { Shield = Amount; }
	
	FORCEINLINE float GetMaxShield() const { return MaxShield; }
	
	/** ********** 淘汰 ********** */
public:
	/** 淘汰玩家 */
	void Elim();

private:
	bool bElimmed = false;
	
	FTimerHandle ElimTimer;

	/** 重生间隔 */
	UPROPERTY(EditDefaultsOnly)
	float ElimDelay = 3.f;
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastElim();
	
	void ElimTimerFinished();

	void DropOrDestroyWeapon(AWeapon* Weapon);

	void DropOrDestroyWeapons();
	
public:
	FORCEINLINE bool IsEliminated() const { return bElimmed; }

	/** ********** 溶解 ********** */
private:
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DissolveTimeline;
	
	FOnTimelineFloat DissolveTrack;
	
	UPROPERTY(EditAnywhere)
	UCurveFloat* DissolveCurve;
	
	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* DynamicDissolveMaterialInstance;
	
	UPROPERTY(EditAnywhere)
	UMaterialInstance* DissolveMaterialInstance;

	void StartDissolve();
	
	UFUNCTION()
	void UpdateDissolveMaterial(float DissolveValue);
	
	/** ********** 机器人 ********** */
private:
	UPROPERTY(EditAnywhere)
	UParticleSystem* ElimBotEffect;
	
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ElimBotComponent;
	
	UPROPERTY(EditAnywhere)
	USoundCue* ElimBotSound;

	/** ********** 开镜 ********** */
public:
	UFUNCTION(BlueprintImplementableEvent)
	void ShowSniperScopeWidget(bool bShowScope);

	/** ********** 默认武器 ********** */
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> DefaultWeaponClass;
	
	void SpawnDefaultWeapon();

	void UpdateHUDAmmo();

	/** ********** 命中盒 ********** */
public:
	UPROPERTY()
	TMap<FName, UBoxComponent*> HitCollisionBoxes;

private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* head;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* pelvis;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* spine_02;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* spine_03;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* upperarm_l;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* upperarm_r;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* lowerarm_l;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* lowerarm_r;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* hand_l;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* hand_r;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* backpack;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* blanket;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* thigh_l;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* thigh_r;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* calf_l;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* calf_r;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* foot_l;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* foot_r;
};