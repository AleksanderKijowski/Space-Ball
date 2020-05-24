#pragma once
#include "stdafx.h"
#include "IOption.hpp"

struct ButtonParams
{
	sf::Vector2f Size;
	sf::Vector2f Position;

	sf::Color* NormalColor;
	sf::Color* HoverColor;
	sf::Color* ClickedColor;

	std::shared_ptr<OptionValueObject> Port;
};