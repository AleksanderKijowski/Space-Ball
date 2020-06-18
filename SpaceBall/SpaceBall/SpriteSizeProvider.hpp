#pragma once
#include "stdafx.h"

class SpriteSizeProvider
{
public:
	sf::Vector2f Get(sf::Sprite sprite)
	{
		return sf::Vector2f(
			sprite.getTexture()->getSize().x * sprite.getScale().x,
			sprite.getTexture()->getSize().y * sprite.getScale().y);
	}
};