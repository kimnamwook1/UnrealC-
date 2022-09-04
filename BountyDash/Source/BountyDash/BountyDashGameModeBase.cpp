// Copyright Epic Games, Inc. All Rights Reserved.


#include "BountyDashGameModeBase.h"
#include "BountyDashCharacter.h"
#include "BountyDashHUD.h"

ABountyDashGameModeBase::ABountyDashGameModeBase()
{

	PrimaryActorTick.bCanEverTick = true;
	//캐릭터를 dnl한 기본 폰 클래스 설정
	DefaultPawnClass = ABountyDashCharacter::StaticClass();

		numCoinsForSpeedIncrease = 5;
		gameSpeed = 10.0F;
		gameSpeedIncrease = 5.0F;
		gameLevel = 1;

		RunTime = 0.0f;
		bGameOver = false;
		startGameOverCount = false;
		timeTillGameOver = 2.0f;
		gameOverTimer = 0.0f;
	
		HUDClass = ABountyDashHUD::StaticClass();
}

void ABountyDashGameModeBase::CharScoreUp(unsigned int charScore)
{
	if (charScore != 0 && charScore % numCoinsForSpeedIncrease == 0)
	{
		gameSpeed += gameSpeedIncrease;
		gameLevel++;

	}
}

float ABountyDashGameModeBase::GetInvGameSpeed()
{
	return -gameSpeed;
}

float ABountyDashGameModeBase::GetGameSpeed()
{
	return gameSpeed;
}

int32 ABountyDashGameModeBase::GetGameLevel()
{
	return gameLevel;
}

void ABountyDashGameModeBase::ReduceGameSpeed()
{
	if (gameSpeed > 10.0f)
	{
		gameSpeed -= gameSpeedIncrease;
		gameLevel--;
	}
}

float ABountyDashGameModeBase::GetRunTime()
{
	return RunTime;
}

void ABountyDashGameModeBase::Tick(float DeltaTime)
{
	if (!startGameOverCount)
	{
		RunTime += DeltaTime;
	}
	else
	{
		gameOverTimer += DeltaTime;
		if (gameOverTimer >= timeTillGameOver)
		{
			bGameOver = true;
		}
	}
}

bool ABountyDashGameModeBase::GetGameOver()
{
	return bGameOver;
}

void ABountyDashGameModeBase::GameOver()
{
	startGameOverCount = true;
}

void ABountyDashGameModeBase::SetGamePaused(bool gamePaused)
{
	APlayerController* myPlayer = GetWorld()->GetFirstPlayerController();
	if (myPlayer != nullptr)
	{
		myPlayer->SetPause(gamePaused);
	}
}
