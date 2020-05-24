#pragma once
#include "stdafx.h"
#include "MainMenuButtonTexts.h"
#include "TextButton.hpp"
#include "MainMenuOptions.hpp"
#include "FileNotFoundException.hpp"

class MainMenuButtonList
{
private:
	sf::Vector2f _scale;
	int _quantity;
	List<std::shared_ptr<Button>> _buttons;

	sf::Color* _normalColor;
	sf::Color* _hoverColor;
	sf::Color* _clickedColor;
	sf::Color* _textColor;

	sf::Font* _font;
	const int _characterSize = 48;

	std::shared_ptr<MainMenuOptions> _port;

public:
	MainMenuButtonList(sf::Vector2f windowSize, std::shared_ptr<MainMenuOptions> port)
	{
		_scale = GetScale(windowSize);
		_quantity = sizeof(MainMenuTexts)/sizeof(*MainMenuTexts);

		_normalColor = new sf::Color(sf::Color::Blue);
		_hoverColor = new sf::Color(sf::Color::Green);
		_clickedColor = new sf::Color(sf::Color::Cyan);
		_textColor = new sf::Color(sf::Color::White);

		_font = new sf::Font();
		
		if (!_font->loadFromFile(DefaultFontPath))
		{
			throw new FileNotFoundException(DefaultFontPath);
		}

		_port = port;

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

	void Update(sf::Vector2i mousePosition, bool isClicked)
	{
		for (var button : _buttons)
		{
			button->Update(mousePosition, isClicked);
		}
	}

	void Render(std::shared_ptr<sf::RenderWindow> target)
	{
		for (var button : _buttons)
		{
			button->Render(target);
		}
	}

private:
	sf::Vector2f GetScale(sf::Vector2f windowSize)
	{
		return sf::Vector2f(windowSize.x / 1920, windowSize.y / 1080);
	}

	void Initialize()
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

		for (var i = 0; i < _quantity; i++)
		{
			params.Position = buttonListPosition + sf::Vector2f(0, (float)i * buttonSize.y);
			params.Text = MainMenuTexts[i];

			params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_port, i + 1));

			var button = new TextButton(params);
			_buttons.push_back(std::shared_ptr<Button>(button));
		}
	}
};