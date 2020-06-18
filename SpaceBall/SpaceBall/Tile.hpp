#pragma once
#include "stdafx.h"

class Tile
{
	friend class Collider;

protected:
	sf::Vector2f _size;
	sf::Vector2f _position;
	sf::Texture* _texture;
	sf::Sprite* _sprite;
	bool _isBreakeable = true;

public:
	Tile(
		sf::Vector2f size,
		sf::Vector2f position,
		sf::Texture* texture,
		bool isBreakable = true)
	{
		_size = size;
		_position = position;
		_texture = texture;
		_isBreakeable = isBreakable;

		_sprite = new sf::Sprite();
		_sprite->setPosition(_position);

		if (_texture != nullptr)
		{
			var textureScale = sf::Vector2f();
			var size = _texture->getSize();
			textureScale.x = _size.x / size.x;
			textureScale.y = _size.y / size.y;
			_sprite->setTexture(*_texture);

			_sprite->setScale(textureScale);
		}
	}

	virtual ~Tile()
	{
		if (_sprite != nullptr)
		{
			delete _sprite;
		}
	}

	virtual void Render(std::shared_ptr<sf::RenderWindow> target)
	{
		if (_sprite != nullptr)
		{
			target->draw(*_sprite);
		}
	}

	bool Breakable() const
	{
		return _isBreakeable;
	}

	virtual sf::RectangleShape GetHitbox() const
	{
		var result = sf::RectangleShape(_size);
		result.setPosition(_position);

		return result;
	}
};