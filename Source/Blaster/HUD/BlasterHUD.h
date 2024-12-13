// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlasterHUD.generated.h"

class UAnnouncement;
class UTexture2D;
class UUserWidget;
class UCharacterOverlay;

USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()
	
public:
	UTexture2D* CrosshairsCenter;
	UTexture2D* CrosshairsLeft;
	UTexture2D* CrosshairsRight;
	UTexture2D* CrosshairsTop;
	UTexture2D* CrosshairsBtoom;
	float CrosshairSpread;
	FLinearColor CrosshairColor;
	
};

UCLASS()
class BLASTER_API ABlasterHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

protected:
	virtual void BeginPlay() override;


	/** ********** 头显 ********** */
public:
	UPROPERTY()
	UCharacterOverlay* CharacterOverlay;
	
	void AddCharacterOverlay();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CharacterOverlayClass;

	/** ********** 公告 ********** */
public:
	UPROPERTY()
	UAnnouncement* Announcement;
	
	void AddAnnouncement();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> AnnouncementClass;

	/** ********** 准星 ********** */
private:
	FHUDPackage HUDPackage;
	
	UPROPERTY(EditAnywhere)
	float CrosshairSpreadMax = 16.f;
	
	void DrawCrosshair(UTexture2D* Texture, FVector2d ViewportCenter, FVector2d Spread, FLinearColor CrosshairColor);

public:
	FORCEINLINE void SetHUDPackage(const FHUDPackage& Package) { HUDPackage = Package; }
};
