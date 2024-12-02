// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"
#include "Projectile.h"
#include "Engine/SkeletalMeshSocket.h"

void AProjectileWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);
	// 确保子弹只在服务器生成
	if (!HasAuthority())
	{
		return;
	}
	APawn* InstigatorPawn = Cast<APawn>(GetOwner());
	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));
	if (MuzzleFlashSocket)
	{
		// 获取Socket的Transform
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		// Socket到目标点的向量
		FVector ToTarget = HitTarget - SocketTransform.GetLocation();
		FRotator TargetRotaion = ToTarget.Rotation();
		if (ProjectileClass && InstigatorPawn)
		{
			// 设置实例化参数
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.Instigator = InstigatorPawn;
			UWorld* World = GetWorld();
			if (World)
			{
				// 实例化炮弹
				World->SpawnActor<AProjectile>(ProjectileClass, SocketTransform.GetLocation(), TargetRotaion, SpawnParams);
			}
		}
	}
}
