#pragma once
#include "stdafx.h"
#include "GameContextShared.hpp"
#include "KeybindsBuilder.hpp"
#include "BuilderButtonSelectionList.hpp"
#include "BuilderButtonSelectionOptions.hpp"
#include "ButtonSelectionField.hpp"
#include "ButtonGrid.hpp"
#include "BuilderGenerateOption.hpp"
#include "FileNotFoundException.hpp"
#include "LevelBuilder.hpp"
#include "MessageBoxState.hpp"

class BuilderContext
{
private:
	sf::Color* _transparentColor;
	sf::Color* _whiteColor;
	sf::Color* _greyColor;
	sf::Color* _blackColor;
	sf::Font* _font;

protected:
	GameContextShared* _context;
	std::shared_ptr<sf::RenderWindow> _window;
	std::shared_ptr<Map<string, int>> _keyBinds;
	std::shared_ptr<BuilderButtonSelectionOptions> _port;
	std::shared_ptr<BuilderGenerateOptions> _generatePort;

	std::shared_ptr<List<sf::Texture*>> _textures;
	std::shared_ptr<BuilderButtonSelectionList> _tileSelection;
	std::shared_ptr<ButtonSelectionField> _buttonSelection;
	std::shared_ptr<ButtonGrid> _buttonGrid;
	std::shared_ptr<TextButton> _generateButton;

	BuilderContext(
		GameContextShared* context,
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<Map<string, int>> supportedKeys)
	{
		_context = context;
		_window = window;
		_keyBinds.reset(KeyBindsBuilder().Build(supportedKeys, BuilderKeyBindsPath));
		_port.reset(new BuilderButtonSelectionOptions());
		_generatePort.reset(new BuilderGenerateOptions());

		InitializeColors();
		InitializeFont();
		InitializeTextures();
		InitializeGenerateButton();

		_tileSelection.reset(new BuilderButtonSelectionList(sf::Vector2f(_window->getSize()), _textures, _port));
		_buttonSelection.reset(new ButtonSelectionField(sf::Vector2f(_window->getSize()), _textures, _port));
		_buttonGrid.reset(new ButtonGrid(sf::Vector2f(_window->getSize()), _textures, _port));
	}

	virtual ~BuilderContext()
	{
		delete _transparentColor;
		delete _whiteColor;
		delete _greyColor;
		delete _blackColor;
		delete _font;
	}

private:
	void InitializeColors()
	{
		_transparentColor = new sf::Color(sf::Color::Transparent);
		_whiteColor = new sf::Color(255, 255, 255, 128);
		_greyColor = new sf::Color(128, 128, 128, 128);
		_blackColor = new sf::Color(sf::Color::Black);
	}

	void InitializeFont()
	{
		_font = new sf::Font();

		if (!_font->loadFromFile(DefaultFontPath))
		{
			throw new FileNotFoundException(DefaultFontPath);
		}
	}

	void InitializeTextures()
	{
		_textures.reset(new List<sf::Texture*>());

		for (var path : BuilderPaths)
		{
			var texture = new sf::Texture();

			if (texture->loadFromFile(path))
			{
				_textures->push_back(texture);
			}
			else
			{
				throw new FileNotFoundException(path);
			}
		}
	}

	void InitializeGenerateButton()
	{
		var screenSize = _window->getSize();
		var scale = ScaleProvider::Get(sf::Vector2f(screenSize));

		var params = TextButtonParams();
		params.Size = sf::Vector2f(1920 * 3 / 12 * scale.x, 1080 * 1 / 6 * scale.y);
		params.Position = sf::Vector2f(1920 * 4 / 6 * scale.x, 1080 * 5 / 6 * scale.y);
		params.NormalColor = _transparentColor;
		params.HoverColor = _whiteColor;
		params.ClickedColor = _greyColor;
		params.TextColor = _blackColor;
		params.Text = GenerateText;
		params.Font = _font;
		params.FontSize = 44;
		params.Port = std::shared_ptr<OptionValueObject>(new OptionValueObject(_generatePort, 1));

		_generateButton.reset(new TextButton(params));
	}
};