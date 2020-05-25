#pragma once
#include "stdafx.h"
#include "IntersectionProvider.hpp"
#include "ButtonState.hpp"
#include "ButtonParams.hpp"

class Button
{
private:
	ButtonState _state;

	sf::Color* _normalColor;
	sf::Color* _hoverColor;
	sf::Color* _clickedColor;

	sf::Color* _current;

	std::shared_ptr<sf::RectangleShape> _shape;

	std::shared_ptr<OptionValueObject> _port;

protected:
	sf::Vector2f _size;
	sf::Vector2f _position;

public:
	Button(ButtonParams params)
	{
		_size = params.Size;
		_position = params.Position;

		_normalColor = params.NormalColor;
		_hoverColor = params.HoverColor;
		_clickedColor = params.ClickedColor;

		_current = _normalColor;

		_shape.reset(new sf::RectangleShape(_size));
		_shape->setPosition(_position);
		_shape->setFillColor(*_current);

		_port = params.Port;
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

					_port->SetValue();
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