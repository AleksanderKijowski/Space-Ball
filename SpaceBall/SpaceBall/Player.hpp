#pragma once
#include "stdafx.h"
#include "ArgumentOutOfRangeException.hpp"
#include "GameStateResources.h"
#include "FileNotFoundException.hpp"
#include "SpriteSizeProvider.hpp"

enum MovementRequest
{
	none,
	left,
	right,
};

class Player : public Tile
{
private:
	sf::Vector2f _boundaries;
	sf::Vector2f _scale;
	float _speed;


public:
	Player(
		sf::Vector2f size,
		sf::Vector2f position,
		sf::Vector2f boundaries,
		sf::Vector2f scale,
		sf::Texture* texture)
		: Tile(size, position, texture)
	{
		_position = position;
		_boundaries = boundaries;
		_scale = scale;
		_speed = 1920 * 4 / 5 / 2 * _scale.x;

		Initialize();
	}

	~Player()
	{
	}

	void Update(float frameTime, MovementRequest request)
	{
		switch (request)
		{
		case none:
			break;

		case left:
			MoveLeft(frameTime);
			break;

		case right:
			MoveRight(frameTime);
			break;

		default:
			throw new ArgumentOutOfRangeException("Player update. Key was: " + std::to_string(request));
		}
	}

	virtual void Render(std::shared_ptr<sf::RenderWindow> target)
	{
		if (_sprite != nullptr)
		{
			target->draw(*_sprite);
		}
	}

private:
	void Initialize()
	{
	}

	void MoveLeft(float timeFrame)
	{
		var position = _sprite->getPosition();
		var spriteSize = SpriteSizeProvider().Get(*_sprite);

		var move = sf::Vector2f(-_speed * timeFrame, 0);
		if (position.x + move.x >= 0)
		{
			_sprite->move(move);
			_position += move;
		}
	}

	void MoveRight(float timeFrame)
	{
		var position = _sprite->getPosition();
		var spriteSize = SpriteSizeProvider().Get(*_sprite);

		var move = sf::Vector2f(_speed * timeFrame, 0);
		if (position.x + move.x + spriteSize.x <= _boundaries.x)
		{
			_sprite->move(move);
			_position += move;
		}
	}
};