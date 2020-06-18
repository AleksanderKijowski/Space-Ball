#pragma once
#include "Tile.hpp"
#include "Ball.hpp"
#include "Player.hpp"

class Collider
{
public:
	bool DoCollide(std::shared_ptr<Tile> tile, std::shared_ptr<Ball> ball)
	{
		var circle = ball->GetHitbox();
		var rectangle = tile->GetHitbox();

		return intersects(circle, rectangle);
	}

	bool DoCollide(std::shared_ptr<Player> player, std::shared_ptr<Ball> ball)
	{
		var circle = ball->GetHitbox();
		var radius = circle.getRadius();
		var rectangle = player->GetHitbox();

		if (circle.getPosition().y + radius >= rectangle.getPosition().y)
		{
			return circle.getPosition().x >= rectangle.getPosition().x && circle.getPosition().x <= rectangle.getPosition().x + rectangle.getSize().x;
		}

		return false;
	}

	float CalculateOffset(std::shared_ptr<Player> player, std::shared_ptr<Ball> ball)
	{
		var circle = ball->GetHitbox();
		var radius = circle.getRadius();
		var rectangle = player->GetHitbox();

		var center = rectangle.getPosition().x + rectangle.getSize().x / 2;

		return 50 * (circle.getPosition().x - center) / rectangle.getSize().x / 2;
	}

	CollisionType DetermineCollisionType(std::shared_ptr<Tile> tile, std::shared_ptr<Ball> ball)
	{
		var circle = ball->GetHitbox();
		var rectangle = tile->GetHitbox();

		var radius = circle.getRadius();
		var circleCenter = circle.getPosition();
		var rec = rectangle.getPosition();

		if (circleCenter.y < rec.y)
		{
			return player;
		}
		else if (circleCenter.y > rec.y && circleCenter.y <= rec.y + rectangle.getSize().y)
		{
			return wall;
		}
		else
		{
			return roof;
		}
	}

private:
	bool intersects(const sf::CircleShape& c, const sf::RectangleShape& r) {
		sf::FloatRect fr = r.getGlobalBounds();
		sf::Vector2f topLeft(fr.left, fr.top);
		sf::Vector2f topRight(fr.left + fr.width, fr.top);
		sf::Vector2f botLeft(fr.left, fr.top + fr.height);
		sf::Vector2f botRight(fr.left + fr.width, fr.top + fr.height);

		return contains(c, topLeft) ||
			contains(c, topRight) ||
			contains(c, botLeft) ||
			contains(c, botRight);
	}

	bool contains(const sf::CircleShape& c, const sf::Vector2f& p) {
		sf::Vector2f center = c.getPosition();
		float a = (p.x - center.x);
		float b = (p.y - center.y);
		a *= a;
		b *= b;
		float r = c.getRadius() * c.getRadius();

		return ((a + b) < r);
	}
};