// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
//탬플릿으로 만들어서 캐스팅 하기 쉽게 하고 다른 객체들의 접근을 용이하게 하기 위해 이곳에 작성
#include "CoreMinimal.h"

template<typename T>
T* GetCustomGameMode(UWorld* worldContext)
{
	return Cast<T>(worldContext->GetAuthGameMode());
}
