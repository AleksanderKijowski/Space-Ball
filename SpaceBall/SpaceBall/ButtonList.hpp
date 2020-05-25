#pragma once
#include "stdafx.h"
#include "TextButton.hpp"
#include "FileNotFoundException.hpp"

class ButtonList
{
protected:
	sf::Vector2f _scale;
	List<std::shared_ptr<Button>> _buttons;

	std::shared_ptr<IOption> _port;

public:
	ButtonList(sf::Vector2f windowSize, std::shared_ptr<IOption> port)
	{
		_scale = GetScale(windowSize);

		_port = port;
	}

	virtual ~ButtonList() = default;

	virtual void Update(sf::Vector2i mousePosition, bool isClicked)
	{
		for (var button : _buttons)
		{
			button->Update(mousePosition, isClicked);
		}
	}

	virtual void Render(std::shared_ptr<sf::RenderWindow> target)
	{
		for (var button : _buttons)
		{
			button->Render(target);
		}
	}

protected:
	sf::Vector2f GetScale(sf::Vector2f windowSize)
	{
		return sf::Vector2f(windowSize.x / 1920, windowSize.y / 1080);
	}

	virtual void Initialize() abstract;
};