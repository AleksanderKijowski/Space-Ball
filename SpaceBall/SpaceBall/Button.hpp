#pragma once
#include "stdafx.h"
#include "IntersectionProvider.hpp"

enum ButtonState
{
	normal,
	hover,
	clicked,
};

struct ButtonParams
{
	sf::Vector2f Size;
	sf::Vector2f Position;

	sf::Color* NormalColor;
	sf::Color* HoverColor;
	sf::Color* ClickedColor;
};

class Button
{
private:
	ButtonState _state;

	sf::Vector2f _size;
	sf::Vector2f _position;

	sf::Color* _normalColor;
	sf::Color* _hoverColor;
	sf::Color* _clickedColor;

	sf::Color* _current;

	sf::RectangleShape* _shape;

protected:
public:
	Button(ButtonParams params)
	{
		_size = params.Size;
		_position = params.Position;

		_normalColor = params.NormalColor;
		_hoverColor = params.HoverColor;
		_clickedColor = params.ClickedColor;

		_current = _normalColor;

		_shape = new sf::RectangleShape(_size);
		_shape->setPosition(_position);
		_shape->setFillColor(*_current);
	}

	virtual void Update(sf::Vector2i mousePosition, bool isClicked)
	{
		if (IntersectionProvider::DoesIntersect(_position, _size, mousePosition))
		{
			if (isClicked)
			{
				if (_state != clicked)
				{
					_state = clicked;
					_current = _clickedColor;

					ButtonStateChanged();
				}
			}
			else
			{
				if (_state != hover)
				{
					_state = hover;
					_current = _hoverColor;

					ButtonStateChanged();
				}
			}
		}
		else
		{
			if (_state != normal)
			{
				_state = normal;
				_current = _normalColor;

				ButtonStateChanged();
			}
		}
	}

	virtual void Render(std::shared_ptr<sf::RenderWindow> target)
	{
		target->draw(*_shape);
	}

protected:
	virtual void ButtonStateChanged()
	{
		_shape->setFillColor(*_current);
	}
};