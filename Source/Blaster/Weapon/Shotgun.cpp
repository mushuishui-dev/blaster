// Fill out your copyright notice in the Description page of Project Settings.

#include "Shotgun.h"
#include "Engine/SkeletalMeshSocket.h"

void AShotgun::Fire(const FVector& HitTarget)
{
	AWeapon::Fire(HitTarget);

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* InstigatorController = OwnerPawn->GetController();
	USkeletalMeshSocket const* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
	if (MuzzleFlashSocket)
	{
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		FVector Start = SocketTransform.GetLocation();
		for (int i = 0; i < NumberOfPellets; i++)
		{
			FVector End = TraceEndWhithScatter(Start, HitTarget);
		}
	}
}
