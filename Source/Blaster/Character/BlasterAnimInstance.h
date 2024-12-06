// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "BlasterAnimInstance.generated.h"

class AWeapon;
class ABlasterCharacter;

UCLASS()
class BLASTER_API UBlasterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
private:
	/**
	 * bool
	 */
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float Speed;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bIsInAir;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bIsAccelerating;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bWeaponEquipped;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bIsCrouched;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bAiming;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bLocallyControlled;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bRotateRootBone;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bElimmed;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float AO_Yaw;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float AO_Pitch;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	ETurningInPlace TurningInPlace;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FTransform LeftHandTransform;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FRotator RightHandRotaion;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool bUseFABRIK;
	
	/**
	 * 偏移
	 */
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float YawOffset;
	FRotator DeltaRotation;

	/**
	 * 倾斜
	 */
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float Lean;
	FRotator CharacterRotationLastFrame;
	FRotator CharacterRotation;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	ABlasterCharacter* BlasterCharacter;
	
	UPROPERTY()
	AWeapon* EquippedWeapon;
	
};
