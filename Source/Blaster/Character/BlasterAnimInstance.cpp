// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterAnimInstance.h"

#include "BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
	// 更新偏航角偏移，控制器X方向和速度X方向的夹角
	// 获取控制器的方向
	FRotator AimRotaion = BlasterCharacter->GetBaseAimRotation();
	// 获取速度的方向
	FRotator MovementRotaion = UKismetMathLibrary::MakeRotFromX(BlasterCharacter->GetVelocity());
	// 计算差值
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(AimRotaion, MovementRotaion);
	// 平滑插值
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaSeconds, 6);
	YawOffset = DeltaRotation.Yaw;
	// 更新倾斜，两帧之间角色旋转X方向的差值
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = BlasterCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	// 按帧更新时间缩放
	const float Target = Delta.Yaw / DeltaSeconds;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaSeconds, 6);
	// 钳制范围
	Lean = FMath::Clamp(Interp, -90, 90);
	// 更新瞄准偏移
	AO_Yaw = BlasterCharacter->GetAO_Yaw();
	AO_Pitch = BlasterCharacter->GetAO_Pitch();
}
