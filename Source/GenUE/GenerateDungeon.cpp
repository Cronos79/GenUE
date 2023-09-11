// (C) Copyright 2023 by CronoGames All Rights Reserved.


#include "GenerateDungeon.h"

UGenerateDungeon::UGenerateDungeon()
{
}

bool UGenerateDungeon::SplitRect(int32 StartSize, int32 DesiredSize, TArray<FGenRect>& Rects)
{
	TArray<FGenRect> TempRects;
	Rects.Empty();
	FGenRect MasterRect;
	MasterRect.Top = 0;
	MasterRect.Left = 0;
	MasterRect.Width = StartSize;
	MasterRect.Height = StartSize;

	if (FMath::RandRange(0, 1))
	{
		SplitRectV(MasterRect, DesiredSize, &TempRects);
	}
	else
	{
		SplitRectH(MasterRect, DesiredSize, &TempRects);
	}

	while (TempRects.Num() > 0)
	{
		FGenRect Rect = TempRects[TempRects.Num() - 1];
		TempRects.RemoveAt(TempRects.Num() - 1, 1, true);
		if (FMath::RandRange(0, 1))
		{
			if (Rect.Width > (DesiredSize * 2) + 1)
			{				
				SplitRectV(Rect, DesiredSize, &TempRects);
			}
			else if (Rect.Height > (DesiredSize * 2) + 1)
			{
				SplitRectH(Rect, DesiredSize, &TempRects);
			}
			else
			{
				Rects.Emplace(Rect);
			}
		}
		else
		{
			if (Rect.Height > (DesiredSize * 2) + 1)
			{
				SplitRectH(Rect, DesiredSize, &TempRects);
			}
			else if (Rect.Width > (DesiredSize * 2) + 1)
			{				
				SplitRectV(Rect, DesiredSize, &TempRects);
			}
			else
			{
				Rects.Emplace(Rect);
			}
		}
	}
	return true;
}

bool UGenerateDungeon::BuildRooms(int32 MinSize, int32 MaxSize, TArray<FGenRect> Rects, TArray<FGenRoom>& Rooms)
{
	for (FGenRect Rect : Rects)
	{
		int32 Width = Rect.Width - 4;
		int32 Height = Rect.Height - 4;
		Width = FMath::Clamp(Width, MinSize, MaxSize);
		Height = FMath::Clamp(Height, MinSize, MaxSize);

		FGenRoom Room;		
		Room.Rect.Top = Rect.Top + 2;
		Room.Rect.Left = Rect.Left + 2;
		Room.Rect.Width = Width;
		Room.Rect.Height = Height;

		Rooms.Add(Room);
	}
	return true;
}

void UGenerateDungeon::SplitRectH(FGenRect Rect, int32 DesiredSize, TArray<FGenRect>* TRect)
{
	int32 Rand = FMath::RandRange(/*Rect.Top + */DesiredSize, Rect.Height - DesiredSize);
	
	FGenRect Rect1;
	Rect1.Top = Rect.Top;
	Rect1.Left = Rect.Left;
	Rect1.Width = Rect.Width;
	Rect1.Height = Rand - 1;
	FGenRect Rect2;
	Rect2.Top = Rect.Top + Rand;
	Rect2.Left = Rect.Left;
	Rect2.Width = Rect.Width;
	Rect2.Height = Rect.Height - Rand;

	TRect->Emplace(Rect1);
	TRect->Emplace(Rect2);
}

void UGenerateDungeon::SplitRectV(FGenRect Rect, int32 DesiredSize, TArray<FGenRect>* TRect)
{
	int32 Rand = FMath::RandRange(/*Rect.Left + */DesiredSize, Rect.Width - DesiredSize);

	FGenRect Rect1;
	Rect1.Top = Rect.Top;
	Rect1.Left = Rect.Left;
	Rect1.Width = Rand - 1;
	Rect1.Height = Rect.Height;
	FGenRect Rect2;
	Rect2.Top = Rect.Top;
	Rect2.Left = Rect.Left + Rand;
	Rect2.Width = Rect.Width - Rand;
	Rect2.Height = Rect.Height;

	TRect->Emplace(Rect1);
	TRect->Emplace(Rect2);
}
