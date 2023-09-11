// (C) Copyright 2023 by CronoGames All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GenerateDungeon.generated.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
	DIRT = 0 UMETA(DisplayName = "Dirt"), 
	STONE_WALL = 0 UMETA(DisplayName = "Stone wall"),
};

USTRUCT(BlueprintType)
struct FGenRect
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Top;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Left;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Width;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Height;
};

USTRUCT(BlueprintType)
struct FGenTile
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ETileType TileType;
};

USTRUCT(BlueprintType)
struct FGenRoom
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FGenTile> Tiles;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FGenRect Rect;	
};

UCLASS(BlueprintType)
class GENUE_API UGenerateDungeon : public UObject
{
	GENERATED_BODY()

public:
	
public:
	UGenerateDungeon();
	UFUNCTION(BlueprintCallable)
	bool SplitRect(int32 StartSize, int32 DesiredSize, TArray<FGenRect>& Rects);
	UFUNCTION(BlueprintCallable)
	bool BuildRooms(int32 MinSize, int32 MaxSize, TArray<FGenRect> Rects, TArray<FGenRoom>& Rooms);
private:
	void SplitRectH(FGenRect Rect, int32 DesiredSize, TArray<FGenRect>* TRect);
	void SplitRectV(FGenRect Rect, int32 DesiredSize, TArray<FGenRect>* TRect);
};
