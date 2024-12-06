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
class ABlasterPlayerState;
class UTimelineComponent;
class ABlasterPlayerController;
class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
class AWeapon;
class UCombatComponent;
class UAnimMontage;

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

	/**
	 * 淘汰
	 */
	UFUNCTION(NetMulticast, Reliable)
	void MulticastElim();
	void Elim();

	/**
	 * 播放Motage
	 */
	void PlayFireMotage(bool bAiming);
	void PlayHitReactMotage();
	void PlayElimMotage();
	void PlayReloadMotage();
	
	virtual void OnRep_ReplicatedMovement() override;

	virtual void Jump() override;
	
protected:
	/**
	 * 输入
	 */
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void EquipButtonPressed();
	void CrouchButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();
	void FireButtonPressed();
	void FireButtonReleased();
	void ReloadButtonPressed();

	/**
	 * 瞄准偏移 or 转身
	 */
	void CalculateAO_Pitch();
	void AimOffset(float DeltaTime);
	void SimProxiesTurn();

	/**
	 * 生命
	 */
	void UpdateHUDHealth();
	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	// 在BeginPlay时PlayerState并未初始化
	void PollInit();
	
private:
	/**
	 * 组件
	 */
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCombatComponent* Combat;

	/**
	 * 武器
	 */
	UPROPERTY(ReplicatedUsing=OnRep_OverlappingWeapon)
	AWeapon* OverlappingWeapon;
	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);
	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	/**
	 * Gameplay
	 */
	UPROPERTY()
	ABlasterPlayerController* BlasterPlayerController;
	UPROPERTY()
	ABlasterPlayerState* BlasterPlayerState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UWidgetComponent* OverheadWidget;

	/**
	 * 瞄准偏移 or 转身
	 */
	float AO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;
	ETurningInPlace TurningInPlace;
	float InterpAO_Yaw;
	bool bRotateRootBone;
	float TurnThreshold = 0.5f;
	FRotator ProxyRotationLastFrame;
	FRotator ProxyRotation;
	float ProxyYaw;
	float TimeSinceLastMovementReplication;
	void TurnInPlace(float DeltaTime);
	float CalculateSpeed();
	
	/**
	 * Motage
	 */
	UPROPERTY(EditAnywhere)
	UAnimMontage* FireWeaponMotage;
	UPROPERTY(EditAnywhere)
	UAnimMontage* HitReactMotage;
	UPROPERTY(EditAnywhere)
	UAnimMontage* ElimMotage;
	UPROPERTY(EditAnywhere)
	UAnimMontage* ReloadMotage;

	/**
	 * 摄像机
	 */
	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;
	void HideCameraIfCharacterClose();

	/**
	 * 生命
	 */
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	UPROPERTY(ReplicatedUsing=OnRep_Health, VisibleAnywhere)
	float Health = 100.f;
	UFUNCTION()
	void OnRep_Health();

	/**
	 * 淘汰
	 */
	bool bElimmed = false;
	FTimerHandle ElimTimer;
	UPROPERTY(EditDefaultsOnly)
	float ElimDelay = 3.f;
	void ElimTimerFinished();

	/**
	 * 溶解
	 */
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DissolveTimeline;
	FOnTimelineFloat DissolveTrack;
	UPROPERTY(EditAnywhere)
	UCurveFloat* DissolveCurve;
	void StartDissolve();
	UFUNCTION()
	void UpdateDissolveMaterial(float DissolveValue);
	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* DynamicDissolveMaterialInstance;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* DissolveMaterialInstance;

	/**
	 * 机器人
	 */
	UPROPERTY(EditAnywhere)
	UParticleSystem* ElimBotEffect;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ElimBotComponent;
	UPROPERTY(EditAnywhere)
	USoundCue* ElimBotSound;

public:
	/**
	 * Getter or Setter
	 */
	void SetOverlappingWeapon(AWeapon* Weapon);
	bool IsWeaponEquipped();
	bool IsAiming();
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }
	AWeapon* GetEquippedWeapon();
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }
	FVector GetHitTarget() const;
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }
	FORCEINLINE bool IsEliminated() const { return bElimmed; }
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	ECombatState GetCombatState() const;
};