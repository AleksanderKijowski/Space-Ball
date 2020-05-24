#pragma once
#include "stdafx.h"
#include "Button.hpp"
#include "TextButton.hpp"

struct TextButtonParams : ButtonParams
{
	string Text;
	int FontSize;
	sf::Color* TextColor;
	sf::Font* Font;
};

class TextButton : public Button
{
private:
	string _textString;
	int _fontSize;
	sf::Color* _textColor;
	sf::Font* _font;

	std::shared_ptr<sf::Text> _text;

public:
	TextButton(TextButtonParams params)
		: Button(params)
	{
		_textString = params.Text;
		_fontSize = params.FontSize;
		_textColor = params.TextColor;
		_font = params.Font;

		_text.reset(new sf::Text());
		_text->setString(_textString);
		_text->setCharacterSize(_fontSize);
		_text->setFillColor(*_textColor);
		_text->setFont(*_font);

		CenterText();
	}

	virtual void Render(std::shared_ptr<sf::RenderWindow> target) override
	{
		Button::Render(target);

		target->draw(*_text);
	}

private:
	void CenterText()
	{
		var textRect = _text->getGlobalBounds();
		_text->setOrigin(sf::Vector2f(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2));
		_text->setPosition(sf::Vector2f(_position.x + _size.x / 2, _position.y + _size.y / 2));
	}
};