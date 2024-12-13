// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"

class ABlasterCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

	friend ABlasterCharacter;
	
public:	
	UBuffComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	/** ********** 组合类 ********** */
private:
	ABlasterCharacter* Character;

	/** ********** 治疗 ********** */
public:
	void Heal(float HealAmout, float HealingTime);

private:
	bool bHealing = false;

	float HealingRate = 0.f;
	
	float AmountToHeal = 0.f;

	void HealRampUp(float DeltaTime);
};
