#pragma once
#include "ButtonList.hpp"
#include "BuilderButtonSelectionOptions.hpp"
#include "BuilderResources.h"
#include "TextureButton.hpp"
#include "FileNotFoundException.hpp"

class BuilderButtonSelectionList : public ButtonList
{
private:
	sf::Color* _transparentColor;
	sf::Color* _textColor;

	std::shared_ptr<List<sf::Texture*>> _textures;
	sf::Font* _font;
	const int _characterSize = 34;

public:
	BuilderButtonSelectionList(sf::Vector2f windowSize, std::shared_ptr<List<sf::Texture*>> textures, std::shared_ptr<BuilderButtonSelectionOptions> port)
		: ButtonList(windowSize, port)
	{
		_transparentColor = new sf::Color(sf::Color::Transparent);
		_textColor = new sf::Color(sf::Color::White);

		_textures = textures;
		_font = new sf::Font();

		if (!_font->loadFromFile(DefaultFontPath))
		{
			throw new FileNotFoundException(DefaultFontPath);
		}

		Initialize();
	}

	virtual ~BuilderButtonSelectionList()
	{
		delete _transparentColor;
		delete _textColor;
		delete _font;
	}

private:

	virtual void Initialize() override
	{
		_buttons = List<std::shared_ptr<Button>>();
		var buttonSize = sf::Vector2f(1920 / 12  * _scale.x, 1080 / 12 * _scale.y);
		var buttonListPosition = sf::Vector2f(1920 / 24 * _scale.x, 1080 / 12 * 2 * _scale.y);
		InitializeButtonSelection(buttonSize, buttonListPosition);
	}

	void InitializeButtonSelection(sf::Vector2f buttonSize, sf::Vector2f buttonListPosition)
	{
		var params = TextureButtonParams();
		params.Size = buttonSize;
		params.Scale = _scale;

		var iterator = 0;
		for (var texture : *_textures)
		{
			params.Position = buttonListPosition + sf::Vector2f(0, buttonSize.y * iterator) + sf::Vector2f(0, buttonSize.y * iterator);
			params.Texture = texture;
			params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_port, iterator + 1));

			_buttons.push_back(std::shared_ptr<TextureButton>(new TextureButton(params)));
		
			++iterator;
		}
	}
};