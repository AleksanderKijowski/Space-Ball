#pragma once
#include "stdafx.h"
#include "MainMenuButtonTexts.h"
#include "MainMenuOptions.hpp"
#include "FileNotFoundException.hpp"
#include "ButtonList.hpp"

class MainMenuButtonList : public ButtonList
{
private:
	const int Quantity = sizeof(MainMenuTexts) / sizeof(*MainMenuTexts);

	sf::Color* _normalColor;
	sf::Color* _hoverColor;
	sf::Color* _clickedColor;
	sf::Color* _textColor;

	sf::Font* _font;
	const int _characterSize = 48;

public:
	MainMenuButtonList(sf::Vector2f windowSize, std::shared_ptr<MainMenuOptions> port)
		: ButtonList(windowSize, port)
	{
		_normalColor = new sf::Color(sf::Color::Transparent);
		_hoverColor = new sf::Color(128, 128, 128, 128);
		_clickedColor = new sf::Color(sf::Color::Transparent);
		_textColor = new sf::Color(sf::Color::Black);

		_font = new sf::Font();
		
		if (!_font->loadFromFile(DefaultFontPath))
		{
			throw new FileNotFoundException(DefaultFontPath);
		}

		Initialize();
	}

	virtual ~MainMenuButtonList()
	{
		delete _normalColor;
		delete _hoverColor;
		delete _clickedColor;
		delete _textColor;
		delete _font;
	}

private:

	virtual void Initialize() override
	{
		var buttonSize = sf::Vector2f(1920 / 6 * 2 * _scale.x, 1080 / 6 * _scale.y);
		var buttonListPosition = sf::Vector2f(1920 / 6 * _scale.x, 1080 / 6 * _scale.y);

		var params = TextButtonParams();
		params.Size = buttonSize;
		params.NormalColor = _normalColor;
		params.HoverColor = _hoverColor;
		params.ClickedColor = _clickedColor;
		params.TextColor = _textColor;
		params.Font = _font;
		params.FontSize = _characterSize * _scale.y;

		for (var i = 0; i < Quantity; i++)
		{
			params.Position = buttonListPosition + sf::Vector2f(0, (float)i * buttonSize.y);
			params.Text = MainMenuTexts[i];

			params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_port, i + 1));

			var button = new TextButton(params);
			_buttons.push_back(std::shared_ptr<Button>(button));
		}
	}
};