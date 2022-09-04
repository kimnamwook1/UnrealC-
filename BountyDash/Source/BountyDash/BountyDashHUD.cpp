// Fill out your copyright notice in the Description page of Project Settings.


#include "BountyDashHUD.h"
#include "Engine/Font.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "BountyDashCharacter.h"
#include "BountyDashGameModeBase.h"

ABountyDashHUD::ABountyDashHUD()
{
	static ConstructorHelpers::FObjectFinder<UFont>OurHudFont(TEXT("Font'/Game/BountyDashFont.BountyDashFont'"));
	
	HUDFont = OurHudFont.Object;
}


void ABountyDashHUD::DrawHUD()
{
	Super::DrawHUD();

	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

	ABountyDashCharacter* DashCharacter = Cast<ABountyDashCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	ABountyDashGameModeBase* DashGameMode = GetCustomGameMode<ABountyDashGameModeBase>(GetWorld());

	FString HUDString = FString::Printf(TEXT("Score: %d Runtime: %.4f"), DashCharacter->GetScore(), DashGameMode->GetRunTime());

	DrawText(HUDString, FColor::Yellow, 50, 50, HUDFont);

	if (DashGameMode->GetGameOver())
	{
		FVector2D GameOverSize;
		GetTextSize(TEXT("GAME OVER!!!   PRESS R to Restart!"), GameOverSize.X, GameOverSize.Y, HUDFont);

		DrawText(TEXT("GAME OVER!!!   PRESS R to Restart!"), FColor::Yellow, (ScreenDimensions.X - GameOverSize.X) / 2.0f, (ScreenDimensions.Y - GameOverSize.Y) / 2.0f, HUDFont);

		DashGameMode->SetGamePaused(true);
	}


}
