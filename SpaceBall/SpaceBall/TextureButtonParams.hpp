#pragma once
#include "stdafx.h"
#include "ButtonParams.hpp"

struct TextureButtonParams : ButtonParams
{
	sf::Texture* Texture;
	sf::Vector2f Scale;
};