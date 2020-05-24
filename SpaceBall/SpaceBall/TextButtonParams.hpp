#pragma once
#include "stdafx.h"
#include "ButtonParams.hpp"

struct TextButtonParams : ButtonParams
{
	string Text;
	int FontSize;
	sf::Color* TextColor;
};