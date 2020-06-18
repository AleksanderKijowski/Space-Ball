#pragma once
#include "stdafx.h"

struct GameStateUpdateParams
{
	float ElapsedTime;

	GameStateUpdateParams(float elapsedTime)
	{
		ElapsedTime = elapsedTime;
	}
};