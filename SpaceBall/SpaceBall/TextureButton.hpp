#pragma once
#include "Button.hpp"
#include "TextureButtonParams.hpp"

class TextureButton : public Button
{
protected:
	sf::Texture* _texture;

	std::shared_ptr<sf::Sprite> _sprite;
	sf::Vector2f _scale;

public:
	TextureButton(TextureButtonParams params)
		: Button(params)
	{
		_texture = params.Texture;
		_scale = params.Scale;

		_sprite.reset(new sf::Sprite());
		TextureChanged();
	}

	virtual void Update(sf::Vector2i mousePosition, bool isClicked) override
	{
		if (isClicked && IntersectionProvider::DoesIntersect(_position, _size, mousePosition))
		{
			_port->SetValue();
		}
	}

	virtual void Render(std::shared_ptr<sf::RenderWindow> target) override
	{
		if (_texture != nullptr)
		{
			target->draw(*_sprite);
		}
	}

	void SetNewTexture(sf::Texture* texture)
	{
		// ToDo: When added animation component it may require changes
		_texture = texture;

		TextureChanged();
	}

	void TextureChanged()
	{
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
};