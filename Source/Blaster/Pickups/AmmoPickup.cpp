// Fill out your copyright notice in the Description page of Project Settings.

#include "AmmoPickup.h"
#include "Blaster/Weapon/WeaponTypes.h"
#include "Blaster/BlasterComponents/CombatComponent.h"
#include "Blaster/Character/BlasterCharacter.h"

AAmmoPickup::AAmmoPickup()
{
	PickupMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_PURPLE);
	PickupMesh->MarkRenderStateDirty();
	PickupMesh->SetRenderCustomDepth(true);
	PickupMesh->SetRelativeScale3D(FVector(4.f, 4.f, 4.f));
}

void AAmmoPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (BlasterCharacter && BlasterCharacter->GetCombat())
	{
		BlasterCharacter->GetCombat()->PickupAmmo(WeaponType, AmmoAmount);
	}

	Destroy();
}
