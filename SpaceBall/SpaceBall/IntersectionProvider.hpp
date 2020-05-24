#pragma once
#include "stdafx.h"

static class IntersectionProvider
{
public:
	static bool DoesIntersect(sf::Vector2f position, sf::Vector2f size, sf::Vector2i coordinates)
	{
		return coordinates.x >= position.x && coordinates.x <= position.x + size.x &&
			coordinates.y >= position.y && coordinates.y <= position.y + size.y;
	}
};