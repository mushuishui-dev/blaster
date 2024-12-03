// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterHUD.h"

void ABlasterHUD::DrawHUD()
{
	Super::DrawHUD();
	FVector2d ViewportSize;
	if (GEngine)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		const FVector2d ViewportCenter((ViewportSize.X / 2.f), ViewportSize.Y / 2.f);
		// 计算准星缩放
		float SpreadScaled = CrosshairSpreadMax * HUDPackage.CrosshairSpread;
		if (HUDPackage.CrosshairsCenter)
		{
			FVector2d Spread(0.f, 0.f);
			DrawCrosshair(HUDPackage.CrosshairsCenter, ViewportCenter, Spread);
		}
		if (HUDPackage.CrosshairsLeft)
		{
			FVector2d Spread(-SpreadScaled, 0.f);
			DrawCrosshair(HUDPackage.CrosshairsLeft, ViewportCenter, Spread);
		}
		if (HUDPackage.CrosshairsRight)
		{
			FVector2d Spread(SpreadScaled, 0.f);
			DrawCrosshair(HUDPackage.CrosshairsRight, ViewportCenter, Spread);
		}
		if (HUDPackage.CrosshairsTop)
		{
			FVector2d Spread(0.f, -SpreadScaled);
			DrawCrosshair(HUDPackage.CrosshairsTop, ViewportCenter, Spread);
		}
		if (HUDPackage.CrosshairsBtoom)
		{
			FVector2d Spread(0.f, SpreadScaled);
			DrawCrosshair(HUDPackage.CrosshairsBtoom, ViewportCenter, Spread);
		}
	}
}

void ABlasterHUD::DrawCrosshair(UTexture2D* Texture, FVector2d ViewportCenter, FVector2D Spread)
{
	// 获取纹理尺寸
	const float TextureWidth = Texture->GetSizeX();
	const float TextureHeight = Texture->GetSizeY();
	const FVector2d TextureDrawPoint(ViewportCenter.X - TextureWidth / 2.f + Spread.X, ViewportCenter.Y - TextureHeight / 2.f + Spread.Y);
	// 绘制贴图
	DrawTexture(Texture, TextureDrawPoint.X, TextureDrawPoint.Y, TextureWidth, TextureHeight, 0.f, 0.f, 1.f, 1.f);
}
