// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"

#include "Components/TextBlock.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		// 更新文本
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	// 获取NetRole
	ENetRole LocalRole = InPawn->GetLocalRole();
	// 构造显示文本
	FString Role;
	switch (LocalRole) {
	case ROLE_None:
		Role = "None";
		break;
	case ROLE_SimulatedProxy:
		Role = "Simulated Proxy";
		break;
	case ROLE_AutonomousProxy:
		Role = "Autonomous Proxy";
		break;
	case ROLE_Authority:
		Role = "Authority";
		break;
	}
	FString LocalRoleString = FString::Printf(TEXT("Local Role: %s"), *Role);
	SetDisplayText(LocalRoleString);
}

void UOverheadWidget::NativeDestruct()
{
	Super::NativeDestruct();
	RemoveFromParent();
}
