#pragma once
#include "stdafx.h"
#include "GameStateResources.h"
#include "FileNotFoundException.hpp"
#include "SpriteSizeProvider.hpp"

enum CollisionType
{
	roof,
	wall,
	player,
};

class Ball
{
	friend class Collider;

private:
	sf::Vector2f _position;
	sf::Vector2f _boundaries;
	sf::Vector2f _scale;
	sf::CircleShape _hitbox;
	float _speed;
	float _angle;

	sf::Texture* _texture;
	sf::Sprite* _sprite;

	bool didCollideWithFloor = false;

public:
	Ball(
		sf::Vector2f position,
		sf::Vector2f boundaries,
		sf::Vector2f scale,
		float angle)
	{
		_position = position;
		_boundaries = boundaries;
		_scale = scale;
		_speed = 1920 * 4 / 5 / 2 * _scale.x;
		_angle = angle;

		Initialize();
	}

	~Ball()
	{
		if (_sprite != nullptr)
		{
			delete _sprite;
		}
	}

	void Update(float frameTime)
	{
		Move(frameTime);
	}

	void Render(std::shared_ptr<sf::RenderWindow> target)
	{
		if (_sprite != nullptr)
		{
			target->draw(*_sprite);
		}
	}

	sf::CircleShape GetHitbox() const
	{
		return _hitbox;
	}

	void OnCollision(CollisionType type, float angleOffset = 0)
	{
		if (_angle > 360)
		{
			_angle -= 360;
		}
		else if (_angle < 0)
		{
			_angle += 360;
		}

		switch (type)
		{
			case wall:
			{
				var alpha = 90 - _angle;
				_angle += 2 * alpha;
				break;
			}

			case roof:
			{
				// -- -> -+
				if (_angle >= 180 && _angle <= 270)
				{
					var alpha = _angle - 180;
					_angle -= 2 * alpha;
				}
				// +- -> ++
				else if (_angle >= 270 && _angle <= 360)
				{
					var alpha = _angle - 270;
					_angle = alpha;
				}

				break;
			}
			case player:
			{
				// -+ -> --
				if (_angle >= 90 && _angle <= 180)
				{
					var alpha = _angle - 90;
					_angle = 270 - alpha - angleOffset;
				}
				// ++ -> +-
				else if (_angle >= 0 && _angle <= 90)
				{
					var alpha = _angle;
					_angle = 360 - alpha - angleOffset;
				}
			}
		}
	}

	bool DidCollideWithFloor()
	{
		return didCollideWithFloor;
	}

private:
	void Initialize()
	{
		_texture = new sf::Texture;
		if (_texture->loadFromFile(BallTexturePath))
		{
			_sprite = new sf::Sprite();
			_sprite->setTexture(*_texture);
			_sprite->setScale(_scale);
			var textureRect = _sprite->getTextureRect();
			_sprite->setOrigin((textureRect.left + textureRect.width) / 2, (textureRect.top + textureRect.height) / 2);
			_sprite->move(_position + sf::Vector2f(0, -textureRect.height / 2));

			_hitbox = sf::CircleShape(SpriteSizeProvider().Get(*_sprite).x);
			_hitbox.setOrigin(_hitbox.getRadius() / 2, _hitbox.getRadius() / 2);
			_hitbox.move(_position + sf::Vector2f(0, -textureRect.height / 2));
		}
		else
		{
			throw new FileNotFoundException(BallTexturePath);
		}
	}

	void Move(float timeFrame)
	{
		var move = sf::Vector2f(
			_speed * cos(_angle * 2 * 3.1415 / 360) * timeFrame,
			_speed * sin(_angle * 2 * 3.1415 / 360) * timeFrame);

		_hitbox.move(move);
		_sprite->move(move);

		var newPosition = _hitbox.getPosition();
		var radius = _hitbox.getRadius();

		if (newPosition.x - radius <= 0 || newPosition.x  + radius >= _boundaries.x)
		{
			OnCollision(wall);
		}
		else if (newPosition.y - radius <= 0)
		{
 			OnCollision(roof);
		}
		else if (newPosition.y + radius >= 1080 * _scale.y)
		{
			didCollideWithFloor = true;
		}
	}
};