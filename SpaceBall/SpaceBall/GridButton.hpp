#pragma once
#include "Button.hpp"

struct GridButtonParams : TextureButtonParams
{
	sf::Color* OutlineColor;
};

class GridButton : public TextureButton
{
private:
	const float _tickness = 1;

	sf::Color* _outlineColor;
	int _value;

public:
	bool isDisabled;

	GridButton(GridButtonParams params)
		: TextureButton(params)
	{
		_outlineColor = params.OutlineColor;

		_shape->setOutlineColor(*_outlineColor);
		_shape->setOutlineThickness(_tickness);

		isDisabled = false;
		_value = 0;
	}
	
	virtual ~GridButton()
	{

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

					isDisabled = true;
					ButtonStateChanged();
				}
			}
			else if (isDisabled && sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				ResetTexture();
				isDisabled = false;
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

		TextureButton::Render(target);
	}

	bool HasTexture()
	{
		return _texture != nullptr;
	}

	int GetValue() const
	{
		return _value;
	}

	void SetValue(int value)
	{
		_value = value;
	}

private:
	void ResetTexture()
	{
		_texture = nullptr;
		SetValue(0);
	}
};