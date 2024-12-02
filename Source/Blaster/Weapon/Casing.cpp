// Fill out your copyright notice in the Description page of Project Settings.


#include "Casing.h"

ACasing::ACasing()
{
	PrimaryActorTick.bCanEverTick = false;
	CasingMesh = CreateDefaultSubobject<UStaticMeshComponent>("CasingMesh");
	SetRootComponent(CasingMesh);
}

void ACasing::BeginPlay()
{
	Super::BeginPlay();
}

void ACasing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

