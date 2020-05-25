#pragma once
#include "stdafx.h"

struct BuilderUpdateParams
{
	bool MouseClicked;
	sf::Vector2i MouseCoordinates;

	BuilderUpdateParams(
		bool mouseClicked,
		sf::Vector2i mouseCoordinates)
	{
		MouseClicked = mouseClicked;
		MouseCoordinates = mouseCoordinates;
	}
};