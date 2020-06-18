#pragma once
#include "stdafx.h"

static class ScaleProvider
{
public:
	ScaleProvider() = default;
	~ScaleProvider() = default;

	static sf::Vector2f Get(sf::Vector2f windowSize)
	{
		return sf::Vector2f(windowSize.x / 1920, windowSize.y / 1080);
	}
};