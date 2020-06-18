#pragma once
#include "stdafx.h"
#include "TextButton.hpp"
#include "FileNotFoundException.hpp"
#include "ScaleProvide.hpp"

class ButtonList
{
protected:
	sf::Vector2f _scale;
	List<std::shared_ptr<Button>> _buttons;

	std::shared_ptr<IOption> _port;

public:
	ButtonList(sf::Vector2f windowSize, std::shared_ptr<IOption> port)
	{
		_scale = ScaleProvider::Get(windowSize);

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
	virtual void Initialize() abstract;
};