// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterAnimInstance.h"

#include "BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	// 获取BlasterCharacter
	BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	// 检查BlasterCharacter
	if (BlasterCharacter == nullptr)
	{
		BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
	}

	// 二次检查BlasterCharacter
	if (BlasterCharacter == nullptr)
	{
		return;
	}

	// 更新速度
	FVector Velocity = BlasterCharacter->GetVelocity();
	Velocity.Z = 0;
	Speed = Velocity.Size();
	// 更新跳跃状态
	bIsInAir = BlasterCharacter->GetCharacterMovement()->IsFalling();
	// 更新加速状态
	bIsAccelerating = BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;
	// 更新武器状态
	bWeaponEquipped = BlasterCharacter->IsWeaponEquipped();
	// 更新下蹲状态
	bIsCrouched = BlasterCharacter->bIsCrouched;
	// 更新瞄准状态
	bAiming = BlasterCharacter->IsAiming();
}
