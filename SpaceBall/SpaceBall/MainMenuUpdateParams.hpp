#pragma once
#include "stdafx.h"

struct MainMenuUpdateParams
{
	bool MouseClicked;
	sf::Vector2i MouseCoordinates;

	MainMenuUpdateParams(
		bool mouseClicked,
		sf::Vector2i mouseCoordinates)
	{
		MouseClicked = mouseClicked;
		MouseCoordinates = mouseCoordinates;
	}
};